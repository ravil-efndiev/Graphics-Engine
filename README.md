# RVL-Engine

### current version: 1.3-a (alpha) (mac build)

RVL Engine is a game developement framkework for C++ and OpenGL

## Short description:
This is object-oriented game dev and graphics framework <br>
Now with RVL Engine you can create basic 2D games, create graphics objects, scenes, cameras and so on <br>
All client-side code is being written in project that includes libRVL.a and RVL.hpp header <br>
It doesn't need any entry point, only basic classes, full tutorial on creating a project you can see in section below

## Project creation guide
Since I have no CLI just use ```git clone https://github.com/ravil-efndiev/RVL-Engine.git``` and go to sandbox folder <br>
There open src and there will be basic project structure and functionality tests <br>
To compile and run type "make" and "./sandbox" or any other executable name you choose in CMakeLists.txt


## Brief documentation (I'm to lazy to write full version, it'll be someday...)
### App
Every RVL program starts with your application class - it is a class that inherits from RvlApp <br>
All basic classes have these virtual methods: Start(), Update() that have to be overridden in child classes <br>
When child RvlApp class is created, it has to call RvlApp constructor that takes game window width, height and title <br>
As you see in an example project - Game class implements all of those three methods <br>
To create and render any objects you can either use Renderer commands directly (which is not recomended), <br>
or create RvlScene child class (see usage is Scenes section)

### Refs and Scopes
Ref and Scope are basically std::shared_ptr and std::unique_ptr <br>
to init Ref use CreateRef<T>() function (std::make_shared wrapper) and CreateScope<T>() (std::make_unique) <br>
also most classes in engine have static Create function that returns Ref of that class (take different parameters, varying on class constructor) <br>
examples:
```cpp
Ref<float> object = CreateRef<float>(10.f); // make_shared<float>(10.f)

Ref<Sprite> sprite1 = CreateRef<Sprite>(glm::vec2(0.f, 5.f), 1.5f); // general sprite initialization
Ref<Sprite> sprite2 = Sprite::Create({0.f, 5.f}, 1.5f); // Sprite-specific initialization
```

### Scenes
Any scene is a class that is inheritedfrom RvlScene class and it is a place where all object creation and rendering happens <br>
Any scene also has Start, Update and Render methods, that should be called in application class <br>
Start and Update work the same, but Render is being called after update when all inside-engine work with scene has been done, and must be used to draw scene objects<br>
RvlApp class has protected member called _currentScene - this is the scene that is curretnly being worked with <br>
In Start of app class initialize your _currentScene with your custom scene class like this:
```cpp
_currentScene = CreateRef<YourSceneClass>();
```
Also every scene has _camera object - Ref of Camera (UserOrhtographicCamera class) which must be initialized in Start() of a scene <br>
example of camera initialization:
```cpp
_camera = Camera::Create();                 // position: 0, 0; zoom: 1
_camera = Camera::Create({1.f, 5.f}, 10.f); // position: 1, 5; zoom: 10
```

You actually mustn't create RvlScene child class

### Classes
#### Rectangle
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; defines rectangle by it's position, width, height and color / transform, color <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; uses flat color shader (no textures) <br>
#### Sprite
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; defines sprite by it's position and scale, texture should be initialized with LoadTexture() <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; void LoadTexture(const std::string& path) - method that sets up texture to the sprite <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; only after texture is initialized sprite can be rendered

### Rendering
Here we'll take only rendering inside RvlScene-child class. <br>
In scene classes all draw calls must be done in Render method, because it takes all boiler-plate scene rendering job and automates it, so you don't have to do it by your own hands <br>
Every primitive class has it's own Draw method, so most of the time, when you create Rectangle or Sprite object you can just do ```cpp object->Draw()```. <br>
Also there is a possibility to workdirectly with renderer using ```cpp Renderer::DrawRect(/*transform*/, /*color or texture*/)```.
example: 
```cpp
Ref<Rectangle> rect = Rectangle::Create(/*positio, scale or transform*/, /*color*/);

// in Render()
rect->Draw();
//or
Renderer::DrawRect(rect->transform(), rect->GetColor());
```

same works with sprites:

```cpp
Ref<Sprite> sprite = Sprite::Create({0.f, 0.f}, 2.f); // 2 is scale of a texture
sprite->LoadTexture("texture.png");

// in Render()
sprite->Draw()
// or
Renderer::DrawRect(sprite->transform(), *sprite->GetTexture());
```

also you can draw rectangles with color or texture directly through renderer without primitives:

```cpp
Renderer::DrawRect({{3.f, 2.f, 0.f}, 45.f, {3.f, 3.f}}, {0.5f, 0.5f, 0.5f}); // color

GLTexture texture ("path.png");
Renderer::DrawRect({{3.f, 2.f, 0.f}, 45.f, {3.f, 3.f}}, texture); // using texture
```

### Entry point
There is no necessity to write int main() by yourself, it is already initialized, but you must specify RvlApp class object <br>
It can be done in OnInit function that returns Scope of type RvlAppe, example:
```cpp
Scope<RvlApp> rvl::OnInit()
{
    return CreateScope<yourAppClass>();
}
```
!IMPORTANT! This function MUST be initialized only once in cpp file where you include EntryPoint.hpp header which has to be included ONLY ONCE
```cpp
// cpp file
#include <RVL/Core/EntryPoint.hpp>

// your code
Scope<RvlApp> rvl::OnInit() {...}
```
