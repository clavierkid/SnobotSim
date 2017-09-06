package com.snobot.simulator.jni;

import org.junit.Assert;
import org.junit.Test;

import com.snobot.test.utilities.BaseSimulatorTest;

import edu.wpi.first.wpilibj.hal.HAL;

public class TestLinking extends BaseSimulatorTest
{
    @Test
	public void testHalLinking()
	{
		Assert.assertTrue(HAL.initialize(0, 0));
	}
}
