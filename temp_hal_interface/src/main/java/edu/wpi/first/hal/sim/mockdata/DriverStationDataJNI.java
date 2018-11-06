package edu.wpi.first.hal.sim.mockdata;

public class DriverStationDataJNI
{
    public static native void setEnabled(boolean b);

    public static native void setDsAttached(boolean b);

    public static native void setAutonomous(boolean aAuton);

    public static native void notifyNewData();

    public static native void setJoystickAxes(byte aJoystickHandle, float[] aAxesArray);

    public static native void setJoystickPOVs(byte aJoystickHandle, short[] aPovsArray);

    public static native void setJoystickButtons(byte aJoystickHandle, int aButtonMask, int aButtonCount);

    public static native void setMatchInfo(String eventName, String gameSpecificMessage, int matchNumber, int replayNumber, int matchType);

}