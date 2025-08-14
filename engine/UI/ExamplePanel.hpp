#pragma once 
#include "UIManager.hpp"

namespace Groove {

	class ExamplePanel : public UIPanel {
	public:
		void OnImGuiRender() override;
	};
}