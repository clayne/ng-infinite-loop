#include "EventListener.h"

auto EventListener::GetSingleton() -> EventListener*
{
	static EventListener singleton{};
	return std::addressof(singleton);
}

auto EventListener::ProcessEvent(
	const RE::BGSActorCellEvent* a_event,
	RE::BSTEventSource<RE::BGSActorCellEvent>* a_eventSource)
	-> RE::BSEventNotifyControl
{
	//

	return RE::BSEventNotifyControl::kContinue;
}
