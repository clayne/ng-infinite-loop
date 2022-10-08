#include "EventListener.h"

using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;

namespace {

	void InitializeLogging() {
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= PluginDeclaration::GetSingleton()->GetName();
		*path += ".log"sv;
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%l] %v"s);
    }

    void InitializeMessaging()
	{
		GetMessagingInterface()->RegisterListener([](MessagingInterface::Message* message) {
			if (message->type == MessagingInterface::kDataLoaded) {
				RE::PlayerCharacter::GetSingleton()->AddEventSink<RE::BGSActorCellEvent>(EventListener::GetSingleton());
			}
		});
	}
}

SKSEPluginLoad(const LoadInterface* skse) {

    auto* plugin = PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();
    log::info("{} {} is loading...", plugin->GetName(), version);

    Init(skse);
	InitializeMessaging();

    log::info("{} has finished loading.", plugin->GetName());
    return true;
}
