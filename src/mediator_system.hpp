/*************************************************************************************************************************************
 * mediator_system.hpp
 * 08-04-2025
 *************************************************************************************************************************************/

#pragma once

#include <memory>
#include <string>
//======================

namespace StrawPen
{

	class Component;

	class Mediator
	{
	public:
		Mediator() = default;
		virtual ~Mediator() = default;

		Mediator(const Mediator& other) = default;
		Mediator(Mediator&& other) noexcept = default;

		Mediator& operator=(const Mediator& other) = default;
		Mediator& operator=(Mediator&& other) = default;

		virtual void notify(Component* sender, std::string event) = 0;
	};  // Mediator

	class Component
	{
	public:
		explicit Component(Mediator* mediator) : m_mediator(mediator) {};
		virtual ~Component() = default;

		Component(const Component& other) = default;
		Component(Component&& other) noexcept = default;

		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) = default;

	protected:
		Mediator* m_mediator = nullptr;
	};  // Component

}  // namespace StrawPen