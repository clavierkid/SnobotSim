
#include <assert.h>
#include <jni.h>
#include "SnobotSim/RobotStateSingleton.h"
#include "SnobotSim/SensorActuatorRegistry.h"
#include "SnobotSim/MotorSim/DcMotorModelConfig.h"
#include "SnobotSim/MotorSim/GravityLoadDcMotorSim.h"
#include "SnobotSim/MotorSim/RotationalLoadDcMotorSim.h"
#include "SnobotSim/MotorSim/StaticLoadDcMotorSim.h"
#include "SnobotSim/MotorSim/SimpleMotorSimulator.h"
#include "SnobotSim/SimulatorComponents/ISimulatorUpdater.h"
#include "SnobotSim/SimulatorComponents/TankDriveSimulator.h"
#include "SnobotSim/SimulatorComponents/Gyro/GyroWrapper.h"
#include <vector>
#include <memory>

static DcMotorModel ConvertDcMotorModel(JNIEnv * env, jobject& aJavaModelConfig)
{
    DcMotorModelConfig config(
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "NOMINAL_VOLTAGE", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "FREE_SPEED_RPM", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "FREE_CURRENT", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "STALL_TORQUE", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "STALL_CURRENT", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mMotorInertia", "D")),

            env->GetBooleanField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mHasBrake", "Z")),
            env->GetBooleanField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mInverted", "Z")),

            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mKT", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mKV", "D")),
            env->GetDoubleField(aJavaModelConfig, env->GetFieldID(env->GetObjectClass(aJavaModelConfig), "mResistance", "D"))
    );

    std::cout << "DcMotorModelConfig [" <<
            "NOMINAL_VOLTAGE=" << config.NOMINAL_VOLTAGE << ", " <<
            "FREE_SPEED_RPM=" << config.FREE_SPEED_RPM << ", " <<
            "FREE_CURRENT=" << config.FREE_CURRENT << ", " <<
            "STALL_TORQUE=" << config.STALL_TORQUE << ", " <<
            "STALL_CURRENT=" << config.STALL_CURRENT << ", " <<
            "mKT=" << config.mKT << ", " <<
            "mKV=" << config.mKV << ", " <<
            "mResistance=" << config.mResistance << ", " <<
            "mMotorInertia=" << config.mMotorInertia << ", " <<
            "mInverted=" << config.mInverted << ", " <<
            "mHasBrake=" << config.mHasBrake << "]" <<
            std::endl;

    return DcMotorModel(config);
}

extern "C"
{
/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    updateLoop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_updateLoop
  (JNIEnv *, jclass)
{
    RobotStateSingleton::Get().UpdateLoop();
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    setSpeedControllerModel_Simple
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_setSpeedControllerModel_1Simple
  (JNIEnv *, jclass, jint aHandle, jdouble aMaxSpeed)
{
    std::shared_ptr<SpeedControllerWrapper> speedController = SensorActuatorRegistry::Get().GetSpeedControllerWrapper(aHandle);
    speedController->SetMotorSimulator(std::shared_ptr < IMotorSimulator > (new SimpleMotorSimulator(aMaxSpeed)));
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    setSpeedControllerModel_Static
 * Signature: (ILcom/snobot/simulator/DcMotorModelConfigJni;DD)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_setSpeedControllerModel_1Static
  (JNIEnv * env, jclass, jint aSpeedControllerHandle,
        jobject aConfig, jdouble aLoad, jdouble aConversionFactor)
{
    DcMotorModel motorModel = ConvertDcMotorModel(env, aConfig);
    std::shared_ptr<SpeedControllerWrapper> speedController = SensorActuatorRegistry::Get().GetSpeedControllerWrapper(aSpeedControllerHandle);
    speedController->SetMotorSimulator(std::shared_ptr < IMotorSimulator > (new StaticLoadDcMotorSim(motorModel, aLoad, aConversionFactor)));
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    setSpeedControllerModel_Gravitational
 * Signature: (ILcom/snobot/simulator/DcMotorModelConfigJni;D)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_setSpeedControllerModel_1Gravitational
  (JNIEnv * env, jclass,
        jint aSpeedControllerHandle, jobject aConfig, jdouble aLoad)
{
    DcMotorModel motorModel = ConvertDcMotorModel(env, aConfig);
    std::shared_ptr<SpeedControllerWrapper> speedController = SensorActuatorRegistry::Get().GetSpeedControllerWrapper(aSpeedControllerHandle);
    speedController->SetMotorSimulator(std::shared_ptr < IMotorSimulator > (new GravityLoadDcMotorSim(motorModel, aLoad)));
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    setSpeedControllerModel_Rotational
 * Signature: (ILcom/snobot/simulator/DcMotorModelConfigJni;DDDD)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_setSpeedControllerModel_1Rotational
  (JNIEnv * env, jclass, jint aSpeedControllerHandle,
        jobject aConfig, jdouble aArmCenterOfMass, jdouble aArmMass, jdouble aConstantAssistTorque, jdouble aOverCenterAssistTorque)
{
    std::cerr << "Unsupported!" << std::endl;
//    DcMotorModel motorModel = ConvertDcMotorModel(aConfig);
//    std::shared_ptr<SpeedControllerWrapper> speedController = SensorActuatorRegistry::Get().GetSpeedControllerWrapper(aSpeedControllerHandle);
//    speedController->SetMotorSimulator(std::shared_ptr < IMotorSimulator > (new StaticLoadDcMotorSimulator(aLoad, aConversionFactor)));
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    connectEncoderAndSpeedController
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_connectEncoderAndSpeedController
  (JNIEnv *, jclass, jint aEncoderhandle, jint aScHandle)
{
    std::shared_ptr<EncoderWrapper> encoder = SensorActuatorRegistry::Get().GetEncoderWrapper(aEncoderhandle);
    std::shared_ptr<SpeedControllerWrapper> speedController = SensorActuatorRegistry::Get().GetSpeedControllerWrapper(aScHandle);

    encoder->SetSpeedController(speedController);
}

/*
 * Class:     com_snobot_simulator_SimulationConnectorJni
 * Method:    connectTankDriveSimulator
 * Signature: (IIID)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_SimulationConnectorJni_connectTankDriveSimulator
  (JNIEnv *, jclass,
          jint aLeftEncHandle,
          jint aRightEncHandle,
          jint aGyroHandle, jdouble aTurnKp)
{    
    std::shared_ptr<EncoderWrapper> leftEncoder = SensorActuatorRegistry::Get().GetEncoderWrapper(aLeftEncHandle);
    std::shared_ptr<EncoderWrapper> rightEncoder = SensorActuatorRegistry::Get().GetEncoderWrapper(aRightEncHandle);
    std::shared_ptr<GyroWrapper> gyro = SensorActuatorRegistry::Get().GetGyroWrapper(aGyroHandle);

    std::shared_ptr<TankDriveSimulator> simulator(new TankDriveSimulator(leftEncoder, rightEncoder, gyro, aTurnKp));

    SensorActuatorRegistry::Get().AddSimulatorComponent(simulator);
}

}
