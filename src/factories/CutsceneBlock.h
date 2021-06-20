#pragma once

#include <Protegon.h>

inline constexpr std::uint32_t CUTSCENE_1_CAMERA_POSITION_1{ ptgn::Color::AsUint32(0,    29, 255, 255) };

using CutsceneFunction = void (*)(ecs::Entity&, ptgn::Timer&, bool& complete);

struct CutsceneTrigger {
	void Update(ecs::Entity& trigger) {
		cutscene(trigger, timer, complete);
	}
	CutsceneFunction cutscene{ nullptr };
	ptgn::Timer timer;
	bool complete{ false };
};

inline void Cutscene1(ecs::Entity& trigger, ptgn::Timer& timer, bool& complete) {
	if (!timer.IsRunning()) {
		trigger.RemoveComponent<ptgn::RigidBodyComponent>();
		timer.Start();
		ptgn::PrintLine("Starting cutscene");
	} else {
		auto elapsed_time = timer.Elapsed<ptgn::milliseconds>();
		assert(trigger.HasComponent<ptgn::ShapeComponent>());
		assert(trigger.HasComponent<ptgn::TransformComponent>());
		static const V2_int original_position = trigger.GetComponent<ptgn::ShapeComponent>().shape->GetCenter(trigger.GetComponent<ptgn::TransformComponent>().transform.position);
		const auto& level = ptgn::LevelManager::GetLevel("level1");
		static const auto destination = level.GetPosition(ptgn::Color::FromUint32(CUTSCENE_1_CAMERA_POSITION_1), { 16, 16 });
		auto& active_camera = ptgn::SceneManager::GetActiveCamera();
		static const auto original_scale = active_camera.scale;
		if (elapsed_time < ptgn::seconds{ 4 }) {
			double elapsed_position_fraction = static_cast<double>(elapsed_time.count()) / static_cast<double>(ptgn::milliseconds{ 3000 }.count());
			double elapsed_zoom_fraction = static_cast<double>(elapsed_time.count()) / static_cast<double>(ptgn::milliseconds{ 2000 }.count());
			elapsed_position_fraction = ptgn::math::Clamp(elapsed_position_fraction, 0.0, 1.0);
			elapsed_zoom_fraction = ptgn::math::Clamp(elapsed_zoom_fraction, 0.0, 1.0);
			active_camera.CenterOn(ptgn::math::Lerp(original_position, destination, elapsed_position_fraction));
			if (elapsed_zoom_fraction != 1.0 && elapsed_zoom_fraction != 0.0) {
				active_camera.scale = ptgn::math::Lerp(original_scale, { 0.85, 0.85 }, elapsed_zoom_fraction);
			}
		} else if (elapsed_time < ptgn::seconds{ 7 }) {
			static bool once = true;
			if (once) {
				ptgn::PrintLine("Opening doors");
				once = false;
			}
			active_camera.CenterOn(destination);
		} else if (elapsed_time < ptgn::seconds{ 10 }) {
			double elapsed_position_fraction = static_cast<double>((ptgn::seconds{ 10 } - elapsed_time).count()) / static_cast<double>(ptgn::milliseconds{ 3000 }.count());
			double elapsed_zoom_fraction = static_cast<double>((ptgn::seconds{ 10 } - elapsed_time).count()) / static_cast<double>(ptgn::milliseconds{ 3000 }.count());
			elapsed_position_fraction = ptgn::math::Clamp(elapsed_position_fraction, 0.0, 1.0);
			elapsed_zoom_fraction = ptgn::math::Clamp(elapsed_zoom_fraction, 0.0, 1.0);
			auto position = ptgn::math::Lerp(destination, original_position, 1.0 - elapsed_position_fraction);
			active_camera.CenterOn(position);
			if (elapsed_zoom_fraction != 1.0 && elapsed_zoom_fraction != 0.0) {
				active_camera.scale = ptgn::math::Lerp({ 0.85, 0.85 }, original_scale, 1.0 - elapsed_zoom_fraction);
			}
		} else {
			ptgn::PrintLine("Cutscene done");
			trigger.AddComponent<ptgn::RigidBodyComponent>();
			complete = true;
		}
	}
}

template <CutsceneFunction TCutscene>
inline void CreateCutsceneTrigger(ecs::Entity& entity, const V2_int& position, const V2_int& size) {
	entity.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	entity.AddComponent<ptgn::ShapeComponent>(ptgn::AABB{ size });
	//entity.AddComponent<ptgn::RenderComponent>();
	//entity.AddComponent<ptgn::ColorComponent>(ptgn::colors::LIGHT_GREY);
	entity.AddComponent<ptgn::HitboxComponent>();
	entity.AddComponent<ptgn::TagComponent>(ptgn::math::Hash("cutscene1_trigger"));
	auto& cutscene_trigger = entity.AddComponent<CutsceneTrigger>();
	cutscene_trigger.cutscene = TCutscene;
}