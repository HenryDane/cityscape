#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif // win32
#include "main.h"
#include "camera.h"
#include "skybox.h"
#include "structure.h"
#include "cube.h"

int width = 2400;
int height = 1800;

EulerCamera camera(width / height, 0, 0, 0);

void init_gl(void);
void config_camera(EulerCamera &cam);

bool c_grabbed = true;

int main() {
    // create the window
    sf::Window window(sf::VideoMode(width, height), "Cityscape", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);
    window.setMouseCursorGrabbed(true);
    hide_cursor();

    // init openGL
    init_gl();

    // init camera
    config_camera(camera);

    skybox_setup();

    std::vector<face_t> faces;
    std::vector<Structure*> objects;
    Cube * c = new Cube(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    objects.push_back(c);
    for(Structure* s : objects)
        s->build(faces);
    for (face_t f : faces)
        std::cout << f.a.str() << " " << f.b.str() << " " << f.c.str() << std::endl;

    // draw variables
    vec2f_t mouseold = {width / 2, height / 2};
    vec2f_t mousedxdy = {0, 0};
    float delta_t = 0;
    sf::Clock clk;
    while (window.isOpen()) {

        // compute mouse dx, dy
        if (c_grabbed) {
            mousedxdy.x = sf::Mouse::getPosition(window).x - mouseold.x;
            mousedxdy.y = - (sf::Mouse::getPosition(window).y - mouseold.y);
            sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);
        } else {
            //mousedxdy = {0, 0};
        }

        // update time
        delta_t = ((float) clk.restart().asMilliseconds()) / 100;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            } else if (event.type == sf::Event::Resized) {
                width = event.size.width;
                height = event.size.height;
                glViewport(0, 0, width, height); // adjust the viewport when the window is resized

                mouseold = {width / 2, height / 2};
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    break;
                } else if (event.key.code == sf::Keyboard::Tab) {
                    if (c_grabbed) {
                        expose_cursor();
                        window.setMouseCursorGrabbed(false);
                        mousedxdy = {0, 0};
                    } else {
                        hide_cursor();
                        window.setMouseCursorGrabbed(true);
                    }

                    c_grabbed = !c_grabbed;
                }
            }
        }

        camera.processMouse(1, mousedxdy);
        camera.processKeyboard(delta_t, 100);

        // handle GL shenanigans
        glLoadIdentity();
        camera.applyTranslations();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO
        glDisable(GL_LIGHTING);
        skybox_draw();
        glEnable(GL_LIGHTING);
        for (face_t f : faces){
            f.draw();
        }

        window.display(); // end the current frame
        //std::cout << delta_t * 100 << " ms per frame" << "\r";
        //std::cout << "DX: " << mousedxdy.x << " DY: " << mousedxdy.y << " " << "DELTA: " << delta_t << " " << std::endl;
        //std::cout << camera.x << " " << camera.y << " " << camera.z << " " << camera.pitch << " " << camera.roll << " " << camera.yaw << std::endl;
    }

    std::cout << std::endl;

    skybox_cleanup();

    return 0;
}


void init_gl() {
    glEnable(GL_TEXTURE_2D);
    glPointSize(3);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    float a[4] = {0, 0, 0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, a);
    float b[4] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, b);
    float c[4] = {0.5, 0.5, 0.5, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, c);
    float d[4] = {0.7, 0.7, 0.7, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.91, 0.91, 0.91, 0.001);
    //glClearColor(0.8, 0.8, 1.0, 0.001);
    //glFogf(GL_FOG_START, 5.0);
    //glFogf(GL_FOG_END, 60.0);
    //glEnable(GL_FOG);
    //glFogi(GL_FOG_MODE, GL_LINEAR);
    //glFogf(GL_FOG_DENSITY, .05);

    //glCullFace(GL_BACK); // halves amount of processing necessary

    //float e[4] = {1.0, 1.0, 1.0, 1.0};
    //glFogfv(GL_FOG_COLOR, e);
}

void config_camera(EulerCamera &cam) {
    cam.setNearClippingPane(0);
    cam.setFarClippingPane(60);
    cam.setFieldOfView(60);
    cam.applyPerspectiveMatrix();
    cam.setPosition(1, 1, 1);
    cam.setRotation(0, 0, 0);
}

vec3f_t calc_normal(vec3f_t a, vec3f_t b, vec3f_t c){
    vec3f_t u = b - a;
    vec3f_t v = c - a;

    vec3f_t n = {0, 0, 0};
    n.x = u.y * v.z - u.z * v.y;
    n.y = u.z * v.x - u.x * v.z;
    n.z = u.x * v.y - u.y * v.x;

    return n;
}

void hide_cursor() {
#ifdef _WIN32
    while (ShowCursor(false) >= 0);
#endif // _win32
}

void expose_cursor() {
#ifdef _WIN32
    while (ShowCursor(true) <= 0);
#endif // _win32
}
