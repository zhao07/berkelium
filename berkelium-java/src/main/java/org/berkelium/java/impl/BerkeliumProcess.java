package org.berkelium.java.impl;

import java.io.IOException;
import java.io.InputStreamReader;

import org.berkelium.java.api.Berkelium;

public class BerkeliumProcess {
	private final static String PREFIX_OUT = "out: ";
	private final static String PREFIX_ERR = "err: ";

	private final Berkelium runtime;
	private final Process process;
	private final InputStreamReader outSr;
	private final InputStreamReader errSr;
	private final StringBuilder outSb = new StringBuilder();
	private final StringBuilder errSb = new StringBuilder();

	public BerkeliumProcess(int port, Berkelium runtime) {
		this.runtime = runtime;
		try {
			process = Runtime.getRuntime().exec("../berkelium/berkelium about:blank --berkelium=127.0.0.1:" + port);
			outSr = new InputStreamReader(process.getInputStream());
			errSr = new InputStreamReader(process.getErrorStream());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public void update() {
		pull(outSr, outSb, PREFIX_OUT);
		pull(errSr, errSb, PREFIX_ERR);
	}

	private void pull(InputStreamReader sr, StringBuilder sb, String prefix) {
		try {
			while(sr.ready()) {
				int c = sr.read();
				if(c == '\n') {
					runtime.log(prefix + sb.toString());
					sb.setLength(0);
					continue;
				}
				sb.append((char)c);
			}
		} catch (IOException e) {
			runtime.handleThrowable(e);
		}
	}

	public void destroy() {
		while(true) {
			try {
				process.exitValue();
				break;
			} catch (IllegalThreadStateException e) {
				// ignore
			}
			update();

			// flush streams...
			if(outSb.length() != 0) {
				runtime.log(PREFIX_OUT + outSb.toString());
			}
			if(errSb.length() != 0) {
				runtime.log(PREFIX_ERR + errSb.toString());
			}

			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				break;
			}
		}
		process.destroy();
		update();
	}
}