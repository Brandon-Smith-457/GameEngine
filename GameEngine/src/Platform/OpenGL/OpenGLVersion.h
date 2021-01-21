#pragma once

namespace GameEngine {

	class OpenGLVersion {
	public:
		static int getVersionMajor();
		static int getVersionMinor();

		static void setVersion(int major, int minor);
		static void OpenGLVersion::shutdown();
	};

}