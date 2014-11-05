#pragma once
#ifndef COMPONENT_H_UTH
#define COMPONENT_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Renderer/RenderAttributes.hpp>
#include <string>
#include <memory>
#include <tinyxml2.h>


namespace uth
{
	class GameObject;
	class RenderTarget;

	class Component
	{
	public:

		Component(const std::string& name); // Should be unique(per gameobject)
		virtual ~Component();

		virtual void SetActive(bool active);
		const bool IsActive() const;

		void SetName(const std::string& name);
		const std::string& GetName() const;

		// Default to doing nothing
		virtual void Init(){}
		virtual void Draw(RenderTarget&){}
		virtual void Update(float){}

		GameObject* parent;

	protected:
		Component();

		std::string m_name;

		bool m_active;

    private:

        friend class GameObject;

        virtual tinyxml2::XMLNode* save() const = 0;
        virtual bool load(const tinyxml2::XMLNode& doc) = 0;

	};
}
#endif