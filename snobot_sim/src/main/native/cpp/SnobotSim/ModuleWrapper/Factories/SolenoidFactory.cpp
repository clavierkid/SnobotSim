/*
 * SolenoidFactory.cpp
 *
 *  Created on: Jun 30, 2018
 *      Author: PJ
 */

#include "SnobotSim/ModuleWrapper/Factories/SolenoidFactory.h"

#include "SnobotSim/Logging/SnobotLogger.h"
#include "SnobotSim/ModuleWrapper/WpiWrappers/WpiSolenoidWrapper.h"
#include "SnobotSim/SensorActuatorRegistry.h"

SolenoidFactory::SolenoidFactory()
{
}

SolenoidFactory::~SolenoidFactory()
{
}

bool SolenoidFactory::Create(int aHandle, const std::string& aType)
{
    bool success = true;

    if (aType == "WpiSolenoidWrapper")
    {
        if (!SensorActuatorRegistry::Get().GetISolenoidWrapper(aHandle, false))
        {
            SNOBOT_LOG(SnobotLogging::WARN, "Not set up before loading robot");

            SensorActuatorRegistry::Get().Register(aHandle,
                    std::shared_ptr<ISolenoidWrapper>(new WpiSolenoidWrapper(aHandle)));
        }
    }
    else
    {
        SNOBOT_LOG(SnobotLogging::WARN, "Unknown type " << aType);
        success = false;
    }

    return success;
}