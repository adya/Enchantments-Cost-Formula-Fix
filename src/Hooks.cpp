#include "Hooks.h"
#include "Hooking.h"
#include "Options.h"

namespace ECFF
{
	struct CalculateCostHook
	{
		static inline constexpr REL::ID     relocation = RELOCATION_ID(50557, 51449);
		static inline constexpr std::size_t offset = OFFSET(0x363, 0x333);

		static float thunk(float enchantingCost, float skillLevel)
		{
			using namespace ECFF::Settings;

			return fEnchantingSkillCostMult() * std::pow(enchantingCost, fEnchantingCostExponent()) * (1.5 - std::exp(-std::pow(skillLevel * fEnchantingSkillCostBase(), fEnchantingSkillCostScale())));
		}

		static inline void post_hook()
		{
			logger::info("\t\t🪝Installed CalculateCostHook hook.");
		}

		static inline REL::Relocation<decltype(thunk)> func;
	};

	void Install()
	{
		stl::install_hook<CalculateCostHook>();
	}
}
