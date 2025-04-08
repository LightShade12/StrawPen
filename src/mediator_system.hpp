#pragma once
#include <memory>
#include <string>

namespace StrawPen
{

	class Component;

	class Mediator
	{
	public:
		Mediator() = default;

		virtual void notify(Component* sender, std::string event) = 0;
	};

	class Component
	{
	public:
		Component(Mediator* mediator) : m_mediator(mediator) {};
		virtual ~Component() = default;

	public:
		Mediator* m_mediator;
	};

}  // namespace StrawPen