#pragma once

class EventListener :
	public RE::BSTEventSink<RE::BGSActorCellEvent>
{
public:
	~EventListener() = default;
	EventListener(const EventListener&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;

	static auto GetSingleton() -> EventListener*;

	auto ProcessEvent(
		const RE::BGSActorCellEvent* a_event,
		RE::BSTEventSource<RE::BGSActorCellEvent>* a_eventSource)
		-> RE::BSEventNotifyControl override;

private:
	EventListener() = default;
};