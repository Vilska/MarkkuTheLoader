#include "cpch.h"
#include "Time.h"

namespace Core {

	std::unique_ptr<DeltaTime::DeltaTimeData> DeltaTime::s_DeltaTimeData = std::make_unique<DeltaTimeData>();

	float DeltaTime::Calculate(float currentFrame)
	{
		s_DeltaTimeData->DeltaTime = currentFrame - s_DeltaTimeData->LastFrame;
		s_DeltaTimeData->LastFrame = currentFrame;

		return s_DeltaTimeData->DeltaTime;
	}
}