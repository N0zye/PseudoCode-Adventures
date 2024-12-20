#include "EventBus.h"

void EventBus::subscribe(EventType type, EventCallback callback) {
	subscribers[type].push_back(callback);
}

void EventBus::unsubscribe(EventType type) {
	subscribers.erase(type);
}

void EventBus::publish(const Event& event) {
	auto type = event.getType();
	auto payload = event.getPayload();
	auto& callbacks = subscribers[type];
	for (auto& callback : callbacks) {
		callback(event);
	}
}