#pragma once
#include <variant>
#include <string>
#include <functional>
#include <map>

enum class EventType {
	RunCodeButtonPressed,

	GameReady,

	LevelSelected, // if LevelSelected payload == -1 reload the current level
	LevelCompleted,
	
	Error,
	// Add more event types here
};

using EventPayload = std::variant<std::monostate, std::string, int, std::vector<std::string>>; 

class Event {
private:
	EventType type;
	EventPayload payload;
public:
	Event(EventType type, EventPayload payload = std::monostate{}) : type(type), payload(payload) {}
	EventType getType() const { return type; }
	EventPayload getPayload() const { return payload; }
};

class EventBus {
public:
	using EventCallback = std::function<void(const Event&)>;
	
	void subscribe(EventType type, EventCallback callback);
	void unsubscribe(EventType type);
	void publish(const Event& event);
private:
	std::map<EventType, std::vector<EventCallback>> subscribers;
	// chat GPT suggested i use a mutex to ensure thread safety, but i'm not sure if that's necessary (there's no multithreading)
	// To lock the mutex, use std::lock_guard<std::mutex> lock(mutex);
	// std::mutex mutex; // include <mutex>
};
