#include <UtH/Platform/Debug.hpp>
#include <cassert>
#include "UtH/Engine/SceneManager.hpp"

#include <UtH/Engine/DefaultScene.hpp>

namespace uth
{
	void defaultNewSceneFunc(int SceneID, Scene* &CurScene)
	{
		switch (SceneID)
		{
		case 0:
			CurScene = new /*Menu*/DefaultScene();
			break;
		case 1:
			CurScene = new /*Game*/DefaultScene();
			break;
		case 2:
			CurScene = new /*Credits*/DefaultScene();
			break;
		default:
			CurScene = new /*Menu*/DefaultScene();
			break;
		}
	}

	SceneManager::SceneManager()
		: m_pendingSceneSwitch(true),
		  m_nextScene(UTHDefaultScene)
	{
		registerNewSceneFunc(defaultNewSceneFunc, 3);
	}
	SceneManager::~SceneManager()
	{
		curScene->DeInit();
		delete curScene;
	}
	
	void SceneManager::GoToScene(int SceneID)
	{
		if (!(UTHDefaultScene <= SceneID && SceneID < sceneCount))
		{
			WriteLog("Error when scene %d switching to %d, number out of range, switching to default scene\n",m_sceneID, m_nextScene);
			m_sceneID = -1;
			return;
		}
		m_pendingSceneSwitch = true;
		m_nextScene = SceneID;
	}

	bool SceneManager::Update(double dt)
	{
		if (m_pendingSceneSwitch)
			m_switchScene();

		if (!curScene->Update(dt))
		{
			WriteLog("Scene %d Update() func returns false\n",m_sceneID);
			return false;
		}
		return true;
	}
	bool SceneManager::Draw()
	{
		if (!curScene->Draw())
		{
			WriteLog("Scene %d Draw() func returns false\n",m_sceneID);
			return false;
		}
		return true;
	}
	
	void SceneManager::registerNewSceneFunc(void (*newSceneFunc)(int SceneID, Scene* &CurScene), int SceneCount)
	{
		makeActiveScene = newSceneFunc;
		sceneCount = SceneCount;
	}

	// private
	void SceneManager::endScene()
	{
		if (!curScene->DeInit())
			WriteLog("Scene %d DeInit() func returns false\n",m_sceneID);
		delete curScene;
	}
	void SceneManager::startScene()
	{
		if (curScene->Init())
			m_sceneID = m_nextScene;
		else
		{
			WriteLog("Scene %d Init() func returns false\n",m_sceneID);
			m_nextScene = -1;
			m_switchScene();
		}
	}

	void SceneManager::m_switchScene()
	{
		if (curScene != nullptr)
			endScene();
		makeActiveScene(m_nextScene,curScene);
		startScene();
		m_pendingSceneSwitch = false;
	}
	
}