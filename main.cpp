#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "main.h"
#include "camera.h"

void init_gl(void);
void config_camera(EulerCamera &camera);

int width = 800;
int height = 600;

int main() {
    // create the window
    sf::Window window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);
    window.setMouseCursorGrabbed(true);

    // init openGL
    init_gl();

    // init camera
    EulerCamera camera(width / height, 0, 0, 0);
    config_camera(camera);

    // draw variables
    vec2f_t mouseold = {width / 2, height / 2};
    vec2f_t mousedxdy = {0, 0};
    float delta_t = 0;
    sf::Clock clk;
    while (window.isOpen()) {
        // compute mouse dx, dy
        mousedxdy.x = sf::Mouse::getPosition(window).x - mouseold.x;
        mousedxdy.y = - (sf::Mouse::getPosition(window).y - mouseold.y);
        sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);

        // update time
        delta_t = ((float) clk.restart().asMilliseconds()) / 100;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            else if (event.type == sf::Event::Resized) {
                width = event.size.width;
                height = event.size.height;
                glViewport(0, 0, width, height); // adjust the viewport when the window is resized
            }
        }

        camera.processMouse(1, mousedxdy);
        camera.processKeyboard(delta_t, 100);

        // handle GL shenanigans
        glLoadIdentity();
        camera.applyTranslations();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        for (Renderable r : objects){
            r.draw();
        }
        // TODO

        window.display(); // end the current frame (internally swaps the front and back buffers)
        //std::cout << "DX: " << mousedxdy.x << " DY: " << mousedxdy.y << " " << "DELTA: " << delta_t << " ";
        //std::cout << camera.x << " " << camera.y << " " << camera.z << " " << camera.pitch << " " << camera.roll << " " << camera.yaw << std::endl;
    }

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
    float a[4] = {0, 8, 100, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, a);
    float b[4] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, b);
    float c[4] = {0.5, 0.5, 0.5, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, c);
    float d[4] = {0.7, 0.7, 0.7, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glClearColor(0.91, 0.91, 0.91, 0.001);
    glClearColor(0.8, 0.8, 1.0, 0.001);
    glFogf(GL_FOG_START, 5.0);
    glFogf(GL_FOG_END, 60.0);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, .05);

    glCullFace(GL_BACK); // halves amount of processing necessary

    float e[4] = {1.0, 1.0, 1.0, 1.0};
    glFogfv(GL_FOG_COLOR, e);
}

void config_camera(EulerCamera &camera) {
    camera.setNearClippingPane(1);
    camera.setFarClippingPane(60);
    camera.setFieldOfView(60);
    camera.applyPerspectiveMatrix();
    camera.setPosition(1, 1, 1);
    camera.setRotation(0, 0, 0);
}
