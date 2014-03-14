#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Text.hpp>

#include <UtH\Platform\Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	//camera.SetViewport(umath::rectangle(0, 0, 1600, 900));
	camera.SetSize(1600, 900);
	camera.SetPosition(0, 0);
	//camera.SetZoom(0);
	//camera.SetRotation(180);

	gameObject.AddComponent(new uth::Sprite("test.tga"));
	//auto sprite = (Sprite*)gameObject.GetComponent("Sprite");
	//sprite->SetColor(1, 0, 1, 1);
	//gameObject.transform.SetSize(0.5f, 0.5f);
	//gameObject.GetComponent("Sprite")->SetActive(false);
	//WriteLog("\nactive: %d", gameObject.transform.GetActive());

	CreateLayer("testi");
	AddGameObjectToLayer(0, &gameObject);
	//AddGameObjectToLayer("testi", &gameObject2);

	gameObject.transform.SetPosition(100,100);
	gameObject.transform.parent->transform.Rotate(30);
	gameObject.transform.SetSize(2, 2);
	gameObject.transform.SetActive(false);

	//RemoveGameObjectFromLayer(0, &gameObject2);
	//RemoveGameObjectFromLayer("testi", &gameObject);

	//layers.at(0)->SetObjectsActive(false);
	layers.at(0)->transform.Move(200,100);

	//SetLayerActive("testi", false);

	//layers.at(0)->transform.SetActive(false);
	layers.at(0)->UpdateTransform();
	WriteLog("\n\nLayerActive: %d",layers.at(0)->transform.GetActive());

	auto text = new Text("kenpixel.ttf");
	text->SetText(L"Testi 123", 30);
	text->SetText(L"Testi 321", 30);

	textObject.AddComponent(text);
	textObject.transform.Move(100, 0);
	AddGameObjectToLayer(0, &textObject);

	return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

bool DefaultScene::Update(double dt)
{
	return true;
}
bool DefaultScene::Draw()
{
	//gameObject.Draw(&shader, &camera);
	//textObject.Draw(&shader, &camera);
	//gameObject.Draw(&shader);
	//gameObject2.Draw(&shader);
	
	for(int i = 0; i < layers.size(); i++)
		layers.at(i)->Draw(&shader);


	return true;
}
