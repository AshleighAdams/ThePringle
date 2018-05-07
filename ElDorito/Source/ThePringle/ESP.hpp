#pragma once

#ifndef __PRINGLE_ESP_
#define __PRINGLE_ESP_

#include "Hooks.hpp"

#include "../Modules/ModuleBase.hpp"
#include "../Utils/Singleton.hpp"

#include "../Blam/BlamPlayers.hpp"
#include "../Blam/BlamObjects.hpp"

#include <mutex>

namespace Pringle
{
	class ESP :
		public Utils::Singleton<ESP>,
		public Modules::ModuleBase
	{
	public:
		ESP();

		Modules::Command* Enabled;
		Modules::Command* Flag1;
		Modules::Command* Flag2;

	protected:
		void Draw(const Hooks::DirectX::EndScene & msg, Blam::Objects::ObjectBase* unit, uint32_t color);
		void Draw(const Hooks::DirectX::EndScene & msg, Blam::Math::RealVector3D _pos, uint32_t color);
		void DrawPlayers(const Hooks::DirectX::EndScene & msg);
		void DrawObjects(const Hooks::DirectX::EndScene & msg);
		void OnEndScene(const Hooks::DirectX::EndScene& msg);
		void UpdatePlayers(const Hooks::PreTick & msg);
		void UpdateObjects(const Hooks::PreTick & msg, Blam::Players::PlayerDatum * localPlayer, Blam::Objects::ObjectBase * localPlayerUnit);
		void OnPreTick(const Hooks::PreTick & msg);

	private:
		std::mutex unit_mutex;
		std::vector<Blam::Objects::ObjectBase*> ally_player_units;
		std::vector<Blam::Objects::ObjectBase*> enemy_player_units;
		std::vector<Blam::Objects::ObjectBase*> hit_enemy_player_units;

		typedef struct {
			Blam::Math::RealVector3D start;
			Blam::Math::RealVector3D end;
		} hit_point_t;

		std::vector<Blam::Objects::ObjectBase*> objects;
		std::vector<Blam::Objects::ObjectBase*> hit_objects;
		std::vector<hit_point_t> hit_points;
	};
}

#endif // !__PRINGLE_ESP_