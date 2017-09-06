package com.snobot.simulator;

import java.util.HashMap;
import java.util.Map;

import com.snobot.simulator.module_wrapper.AnalogWrapper;
import com.snobot.simulator.module_wrapper.DigitalSourceWrapper;
import com.snobot.simulator.module_wrapper.EncoderWrapper;
import com.snobot.simulator.module_wrapper.RelayWrapper;
import com.snobot.simulator.module_wrapper.SolenoidWrapper;
import com.snobot.simulator.module_wrapper.SpeedControllerWrapper;
import com.snobot.simulator.simulator_components.gyro.GyroWrapper;

public class SensorActuatorRegistry
{
    private static SensorActuatorRegistry mInstance = new SensorActuatorRegistry();

    private Map<Integer, SpeedControllerWrapper> mSpeedControllerMap = new HashMap<>();
    private Map<Integer, RelayWrapper> mRelayWrapperMap = new HashMap<>();
    private Map<Integer, DigitalSourceWrapper> mDigitalSourceWrapperMap = new HashMap<>();
    private Map<Integer, AnalogWrapper> mAnalogSourceWrapperMap = new HashMap<>();
    private Map<Integer, SolenoidWrapper> mSolenoidWrapperMap = new HashMap<>();
    private Map<Integer, EncoderWrapper> mEncoderWrapperMap = new HashMap<>();
    private Map<Integer, GyroWrapper> mGyroWrapperMap = new HashMap<>();

    private SensorActuatorRegistry()
    {

    }

    public static SensorActuatorRegistry get()
    {
        return mInstance;
    }

    public <ItemType> boolean registerItem(ItemType aItem, int aPort, Map<Integer, ItemType> aMap, String aMessage)
    {
        if (aMap.containsKey(aPort) || aPort < 0)
        {
            return false;
        }
        aMap.put(aPort, aItem);

        return true;
    }

    public boolean register(AnalogWrapper aActuator, int aPort)
    {
        return registerItem(aActuator, aPort, mAnalogSourceWrapperMap, "Analog");
    }

    public boolean register(SpeedControllerWrapper aActuator, int aPort)
    {
        return registerItem(aActuator, aPort, mSpeedControllerMap, "Speed Controller");
    }

    public boolean register(DigitalSourceWrapper aSensor, int aPort)
    {
        return registerItem(aSensor, aPort, mDigitalSourceWrapperMap, "Digital IO");
    }

    public boolean register(SolenoidWrapper aActuator, int aPort)
    {
        return registerItem(aActuator, aPort, mSolenoidWrapperMap, "Solenoid");
    }

    public boolean register(RelayWrapper aActuator, int aPort)
    {
        return registerItem(aActuator, aPort, mRelayWrapperMap, "Relay");
    }

    public boolean register(EncoderWrapper aEncoder, Integer aPort)
    {
        return registerItem(aEncoder, aPort, mEncoderWrapperMap, "Encoder");
    }

    public boolean register(GyroWrapper aSensor, Integer aPort)
    {
        return registerItem(aSensor, aPort, mGyroWrapperMap, "Gyro");
    }

    public Map<Integer, SpeedControllerWrapper> getSpeedControllers()
    {
        return mSpeedControllerMap;
    }

    public Map<Integer, SolenoidWrapper> getSolenoids()
    {
        return mSolenoidWrapperMap;
    }

    public Map<Integer, DigitalSourceWrapper> getDigitalSources()
    {
        return mDigitalSourceWrapperMap;
    }

    public Map<Integer, RelayWrapper> getRelays()
    {
        return mRelayWrapperMap;
    }

    public Map<Integer, AnalogWrapper> getAnalog()
    {
        return mAnalogSourceWrapperMap;
    }

    public Map<Integer, EncoderWrapper> geEncoders()
    {
        return mEncoderWrapperMap;
    }

    public void reset()
    {
        mSpeedControllerMap.clear();
        mRelayWrapperMap.clear();
        mDigitalSourceWrapperMap.clear();
        mAnalogSourceWrapperMap.clear();
        mSolenoidWrapperMap.clear();
        mEncoderWrapperMap.clear();
        mGyroWrapperMap.clear();
    }
}
