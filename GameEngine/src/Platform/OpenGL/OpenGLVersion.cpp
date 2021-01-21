#include "gepch.h"
#include "Platform/OpenGL/OpenGLVersion.h"

namespace GameEngine {

	struct VersionStorage {
		int versionMajor;
		int versionMinor;
	};

	static VersionStorage* s_Data = nullptr;

	int OpenGLVersion::getVersionMajor() {
		return s_Data->versionMajor;
	}

	int OpenGLVersion::getVersionMinor()
	{
		return s_Data->versionMinor;
	}

	void OpenGLVersion::setVersion(int major, int minor) {
		if (s_Data == nullptr) s_Data = new VersionStorage();

		s_Data->versionMajor = major;
		s_Data->versionMinor = minor;
	}

	void OpenGLVersion::shutdown() {
		delete s_Data;
	}

}