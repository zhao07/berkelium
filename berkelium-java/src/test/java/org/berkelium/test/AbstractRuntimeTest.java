package org.berkelium.test;

import java.util.LinkedList;

import org.berkelium.api.Runtime;
import org.berkelium.impl.TestHelper;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public abstract class AbstractRuntimeTest {
	private LinkedList<Integer> objectCount = new LinkedList<Integer>();
	private LinkedList<String> objectDump = new LinkedList<String>();
	protected Runtime runtime;

	protected Runtime createRuntime() {
		return TestHelper.createRuntime();
	}

	@Before
	public void before() {
		pushObjectCount();
		runtime = createRuntime();
		Assert.assertNotNull(runtime);
		assertChangedAndPush();
	}

	@After
	public void after() {
		assertUnchanged();
		runtime.dispose();
		runtime = null;
		popAndAssert();
		Assert.assertEquals(1, objectCount.size());
		Assert.assertEquals(1, objectDump.size());
	}

	protected void pushObjectCount() {
		objectCount.addLast(TestHelper.getObjectCount());
		objectDump.addLast(getStats());
	}

	protected void popAndAssert() {
		objectCount.removeLast();
		objectDump.removeLast();
		assertUnchanged();
	}

	protected void assertChanged() {
		Assert.assertNotEquals(objectCount.peekLast(), TestHelper.getObjectCount());
		/* TODO check memory leaks in berkelium
		Assert.assertNotEquals(objectDump.peekLast(), getStats());
		*/
	}

	protected void assertUnchanged() {
		Assert.assertEquals(objectCount.peekLast(), TestHelper.getObjectCount());
		/* TODO check memory leaks in berkelium
		Assert.assertEquals(objectDump.peekLast(), getStats());
		*/
	}

	protected void assertChangedAndPush() {
		assertChanged();
		pushObjectCount();
	}

	private String getStats() {
		if(runtime == null) {
			return null;
		}
		return runtime.getDebugObjectStats();
	}

	@Test
	public void testBeforeAndAfter() {
	}
}
