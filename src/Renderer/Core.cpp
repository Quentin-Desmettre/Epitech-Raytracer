///*
//** EPITECH PROJECT, 2023
//** Epitech-Raytracer
//** File description:
//** Renderer
//*/
//
//#include "Renderer.hpp"
//
//Renderer::Renderer()
//{
//    _vertexArray.resize(WINDOW_SIZE.x * WINDOW_SIZE.y);
//    for (size_t i = 0; i < _vertexArray.getVertexCount(); i++)
//        _vertexArray[i].position = sf::Vector2f(i % (int)WINDOW_SIZE.x, i / WINDOW_SIZE.x);
//    _pixels.reserve(WINDOW_SIZE.x * WINDOW_SIZE.y);
//}
//
//void Renderer::handleMovement(sf::Event event)
//{
//    bool reset = false;
//
//    if (event.key.code == sf::Keyboard::Z)
//        _camera.move(Camera::FORWARD, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::S)
//        _camera.move(Camera::BACKWARD, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::Q)
//        _camera.move(Camera::LEFT, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::D)
//        _camera.move(Camera::RIGHT, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::A)
//        _camera.move(Camera::UP, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::E)
//        _camera.move(Camera::DOWN, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::Up)
//        _camera.turn(0.1f, 0, reset);
//    if (event.key.code == sf::Keyboard::Down)
//        _camera.turn(-0.1f, 0, reset);
//    if (event.key.code == sf::Keyboard::Left)
//        _camera.turn(0, -0.1f, reset);
//    if (event.key.code == sf::Keyboard::Right)
//        _camera.turn(0, 0.1f, reset);
//    if (event.key.code == sf::Keyboard::Enter)
//        drawToFile();
//
//    if (reset)
//        resetPixels();
//}
//
//void Renderer::run(Scene *pool, Camera &camera)
//{
//    _camera = camera;
//    _camera.updateRayDirs();
//    // creating window of size WINDOW_SIZE (change WINDOW_SIZE in Camera.hpp)
//    _window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "RayTracer");
//    while (_window.isOpen()) {
//        sf::Event event;
//        while (_window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed ||
//            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
//                drawToFile();
//                _window.close();
//                return;
//            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
//            && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
//                addSphereAtPos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), pool);
//            else if (event.type == sf::Event::KeyPressed)
//                handleMovement(event);
//        }
//        // using threads or not to render
//        if (!_threads)
//            perThread(0, WINDOW_SIZE.x, pool);
//        else {
//            for (uint i = 0; i < NB_THREADS; i++)
//                _threadPool.push_back(std::thread(&Renderer::perThread, this,
//                i * WINDOW_SIZE.x / NB_THREADS, (i + 1) * WINDOW_SIZE.x / NB_THREADS, pool));
//            for (uint i = 0; i < NB_THREADS; i++)
//                _threadPool[i].join();
//            _threadPool.clear();
//        }
//        draw();
//    }
//}
//
//void Renderer::perThread(int startX, int endX, const Scene *pool)
//{
//    for (int x = startX; x < endX; x++) {
//        for (int y = 0; y < WINDOW_SIZE.y; y++) {
//            Vec3 colors = Vec3(0, 0, 0);
//            // calculating averabe between multiple rays for better precision
//            // (change RAYS_PER_PIXEL in Renderer.hpp)
//            for (float i = 0; i < RAYS_PER_PIXEL; i++)
//                colors += getPixelFColor(sf::Vector2f(x, y), pool);
//            colors /= RAYS_PER_PIXEL;
//            addPixel(sf::Vector2f(x, y), colors);
//        }
//    }
//}
//
//Vec3 Renderer::getPixelFColor(sf::Vector2f pos, const Scene *pool) const
//{
//    Vec3 rayColor = Vec3(1, 1, 1);
//    Vec3 light = VEC3_ZERO;
//    Ray ray = Ray(_camera.getPos(), _camera.getRayDir(pos));
//    const AObject *old = nullptr;
//    float lightIntensity = 1;
//
//    for (int bounces = 0; bounces <= NB_BOUNCE; bounces++) {
//        const AObject *obj = pool->getClosest(ray, old);
//
//        if (!obj)
//            break;
//        Vec3 inter = obj->getIntersection(ray);
//        Vec3 normal = obj->getNormal(inter, ray);
//        // calcualte light angle with object
//        float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);
//        // add light of object according to its color and other parameters
//        light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity() * lightIntensity;
//
//        // updating ray for next iteration
//        rayColor *= obj->getColor();
//        ray.setOrigin(inter);
//        ray.reflect(normal, obj->getReflectivity());
//
//        // adding light of sun and light points
//        light += addSunLight(normal, inter, rayColor, pool, obj) * lightIntensity;
//        light += addLightOfPoints(normal, inter, rayColor, pool, obj) * lightIntensity;
//
//        // reducing light intensity for next iteration
//        lightIntensity *= 0.6;
//        old = obj;
//    }
//    // adding ambient light
//    light += rayColor * getAmbientLight(pos);
//    return light;
//}
//
//void Renderer::addPixel(sf::Vector2f pos, Vec3 color)
//{
//    Vec3 trueColor = color;
//
//    // averaging color if smooth is enabled
//    if (_nbFrames == 1)
//        _pixels[pos.y * WINDOW_SIZE.x + pos.x] = color;
//    else if (_smooth) {
//        _pixels[pos.y * WINDOW_SIZE.x + pos.x] += color;
//        trueColor = _pixels[pos.y * WINDOW_SIZE.x + pos.x] / _nbFrames;
//    }
//
//    // converting trueColor (0-1) to sf::Color (0-255)
//    trueColor *= 255.0f;
//    trueColor.x = std::min(trueColor.x, 255.0f);
//    trueColor.y = std::min(trueColor.y, 255.0f);
//    trueColor.z = std::min(trueColor.z, 255.0f);
//
//    // adding color to vertex array
//    _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].color = sf::Color(trueColor.x, trueColor.y, trueColor.z);
//}
//
//void Renderer::addSphereAtPos(sf::Vector2f pos, Scene *pool)
//{
//    // calculating sphere position
//    Ray ray = Ray(_camera.getPos(), _camera.getRayDir(pos));
//    Vec3 inter = ray.getOrigin() + Math::normalize(ray.getDir()) * 10.0f;
//    const AObject *obj = pool->getClosest(ray);
//    Sphere *sphere = new Sphere(inter, sf::Color(255, 64, 64), 0.5f);
//
//    // setting sphere position if there is an intersection
//    if (obj != nullptr)
//        sphere->setPos(obj->getIntersection(ray));
//    pool->addObject(sphere);
//    resetPixels();
//}
//
//void Renderer::draw() {
//    #if DEBUG
//        static float avgPerfs = 0;
//
//        if (_nbFrames == 0)
//            avgPerfs = clock.getElapsedTime().asSeconds();
//        else
//            avgPerfs = (avgPerfs * _nbFrames + clock.getElapsedTime().asSeconds()) / (_nbFrames + 1);
//        std::cout << "Render in " << clock.getElapsedTime().asSeconds() << "s"
//        << "\t(avg: " << avgPerfs << "s)" << std::endl;
//        clock.restart();
//    #endif
//    _window.clear();
//    _window.draw(_vertexArray);
//    _window.display();
//    _nbFrames++;
//}
//
//void Renderer::drawToFile() {
//    sf::Texture texture;
//    texture.create(_window.getSize().x, _window.getSize().y);
//    texture.update(_window);
//    texture.copyToImage().saveToFile("renders/render.png");
//};
