# GameEngine
A (soon to be) platform independent generalized game engine with (eventual) support for multiple different graphics API's.  Inspired and based on TheCherno's <a href="https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT" target="_blank">Game Engine Series</a> (<a href="https://github.com/TheCherno/Hazel" target="_blank">Hazel</a>).  
  
*Compilation steps:*
* Install visual studio or any other C++ compiler supported by Premake.
* Git clone the repository and all submodules (Example: git clone --recursive https://github.com/Brandon-Smith-457/GameEngine.git).
* Run the batch file inside the scripts directory.
* Open the .sln in Visual Studio (or whatever compiler used) and compile / run the engine.
  * Note: If you are running an antivirus on your computer then it might flag the executable with "suspicious activity".

*Implementation details:*
* Logging implemented using <a href="https://github.com/gabime/spdlog" target="_blank">spdlog</a>.
* Build procedures made simple using <a href="https://github.com/premake/premake-core" target="_blank">premake5.0</a>.
* Window features implemented using <a href="https://github.com/glfw/glfw" target="_blank">GLFW</a>.
* OpenGL API <a href="https://glad.dav1d.de/" target="_blank">Glad</a> used for more advanced features than basic OpenGL.
* <a href="https://github.com/ocornut/imgui" target="_blank">Imgui</a> GUI library being used to save time on writing a GUI library.
* Maths library <a href="https://github.com/g-truc/glm" target="_blank">OpenGL Mathematics</a> used to take advantage of math procedures executing in fewer CPU instructions by taking advantage of register based calculation.
* Image loading done with <a href="https://github.com/nothings/stb" target="_blank">stb_image</a> to efficiently load in image data and parse the data type without having to parse binaries in my own code.