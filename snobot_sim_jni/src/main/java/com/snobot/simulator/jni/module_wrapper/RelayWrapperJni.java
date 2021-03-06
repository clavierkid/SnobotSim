
package com.snobot.simulator.jni.module_wrapper;

import com.snobot.simulator.jni.BaseSimulatorJni;

public final class RelayWrapperJni extends BaseSimulatorJni
{
    private RelayWrapperJni()
    {

    }

    public static native boolean isInitialized(int aPort);

    public static native void setName(int aPort, String aName);

    public static native String getName(int aPort);

    public static native boolean getWantsHidden(int aPort);

    public static native boolean createSimulator(int aPort, String aType);

    public static native void removeSimluator(int aPort);

    public static native boolean getFowardValue(int aPort);

    public static native boolean getReverseValue(int aPort);

    public static native int[] getPortList();
}
