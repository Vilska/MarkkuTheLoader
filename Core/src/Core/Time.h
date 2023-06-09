#pragma once

#include <memory>

namespace Core {

	class DeltaTime
	{
	public:
		static float Calculate(float currentFrame);
	private:
		struct DeltaTimeData
		{
			float DeltaTime;
			float LastFrame;
		};

		static std::unique_ptr<DeltaTimeData> s_DeltaTimeData;
	};

}
