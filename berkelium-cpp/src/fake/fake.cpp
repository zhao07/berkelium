// Copyright (c) 2013 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <Berkelium/API/Runtime.hpp>
#include <Berkelium/API/Util.hpp>
#include <Berkelium/API/Profile.hpp>
#include <Berkelium/API/BerkeliumFactory.hpp>
#include <Berkelium/IPC/Message.hpp>
#include <Berkelium/IPC/Channel.hpp>
#include <Berkelium/IPC/ChannelGroup.hpp>
#include <Berkelium/Impl/Impl.hpp>

#include <queue>

using Berkelium::RuntimeRef;
using Berkelium::BerkeliumFactory;
using Berkelium::ProfileRef;
using Berkelium::LoggerRef;
using Berkelium::Ipc::Channel;
using Berkelium::Ipc::ChannelRef;
using Berkelium::Ipc::ChannelGroup;
using Berkelium::Ipc::ChannelGroupRef;
using Berkelium::Ipc::Message;
using Berkelium::Ipc::MessageRef;
using Berkelium::Ipc::CommandId;

using Berkelium::Util::getOption;

struct Entry {
	int64_t time;
	ChannelRef channel;
	MessageRef msg;

	Entry(int64_t time, ChannelRef channel, MessageRef msg) :
		time(time + Berkelium::Util::currentTimeMillis()),
		channel(channel),
		msg(msg) {
	}
};

class EntrySort {
public:
	EntrySort() {
	}

	bool operator() (const Entry& lhs, const Entry& rhs) const {
		return lhs.time < rhs.time;
	}
};

int main(int argc, char* argv[])
{
	Berkelium::impl::enableBerkeliumHostMode();
	Berkelium::RuntimeRef runtime(Berkelium::Util::createRuntime(argc, argv));
	Berkelium::LoggerRef logger(runtime->getLogger("main", "main"));

	std::string dir = getOption(argc, argv, "--user-data-dir=");
	std::string id = getOption(argc, argv, "--berkelium=");

	if(dir.empty() || id.empty()) {
		logger->error() << "profile or id not given!" << std::endl;
		return 1;
	}

	ProfileRef profile = runtime->forProfilePath(dir);
	if(!profile->isFound()) {
		logger->error() << "profile not found!" << std::endl;
		return 1;
	}
	if(profile->isInUse()) {
		logger->error() << "profile already in use!" << std::endl;
		return 1;
	}
	profile->setLocked(true);
	if(!profile->isLocked()) {
		logger->error() << "profile can not be locked!" << std::endl;
		return 1;
	}

	ChannelGroupRef group(ChannelGroup::create());

	logger->debug() << "starting host fake!" << std::endl;
	ChannelRef ipc = Channel::getChannel(group, logger, dir, id, false);

	MessageRef msg(ipc->getMessage());
	msg->add_str("berkelium");
	ipc->send(msg);

	logger->info() << "host fake started!" << std::endl;

	bool running = true;
	std::list<ChannelRef> channels;
	channels.push_front(ipc);

	std::priority_queue<Entry, std::vector<Entry>, EntrySort> todo;

	while(running) {
		bool wait = true;
		for(std::list<ChannelRef>::iterator it = channels.begin(); it != channels.end(); it++) {
			if(!running) {
				break;
			}
			ChannelRef ipc = *it;

			if(ipc->isEmpty()) {
				continue;
			}
			wait = false;

			ipc->recv(msg);
			bool sendAck = false;

			switch(CommandId cmd = msg->get_cmd()) {
				default: {
					logger->error() << "received unknown command '" << cmd << "'" << std::endl;
					sendAck = true;
					break;
				}

				case CommandId::exitHost: {
					running = false;
					sendAck = true;
					break;
				}

				case CommandId::createTab: {
					ChannelRef tab(ipc->createSubChannel());
					ChannelRef tab2(tab->getReverseChannel());
					channels.push_back(tab);
					msg->reset();
					msg->add_str(tab->getName());
					ipc->send(msg);
					logger->info() << "created new tab with id " << tab->getName() << "!" << std::endl;

					// wait 2s and send onReady
					MessageRef m = Message::create(logger);
					m->add_cmd(CommandId::onReady);
					todo.push(Entry(2000, tab2, m));
					msg->reset();
					break;
				}

				case CommandId::createWindow: {
					bool incognito = msg->get_8() == 1;
					ChannelRef win(ipc->createSubChannel());
					channels.push_back(win);
					msg->reset();
					msg->add_str(win->getName());
					ipc->send(msg);
					logger->info() << "created new " << (incognito ? "incognito" : "default") << " window with id "
							<< win->getName() << "!" << std::endl;
					break;
				}

				case CommandId::navigate: {
					std::string url(msg->get_str());
					logger->info() << "navigate to '" << url << "'" << std::endl;
					break;
				}
			}

			if(sendAck) {
				msg->reset();
				ipc->send(msg); // ACK
			}
		}

		while(!todo.empty()) {
			Entry entry = todo.top();
			if(entry.time > Berkelium::Util::currentTimeMillis()) {
				break;
			}
			todo.pop();
			logger->info() << "processing queued task..." << std::endl;
			entry.channel->send(entry.msg);
		}

		if(wait) {
#ifdef LINUX
			usleep(33000);
#else
#error TODO
#endif
		}
	}

	logger->info() << "host fake done!" << std::endl;

	return 0;
}
