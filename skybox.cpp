#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include "main.h"

sf::Texture * _tex_dat;

void skybox_setup(){
    glEnable(GL_TEXTURE_2D);

    _tex_dat = new sf::Texture[6];

    _tex_dat[0].loadFromFile("res/miramar_lf.tga"); // bk
    _tex_dat[1].loadFromFile("res/miramar_ft.tga"); // lf
    _tex_dat[2].loadFromFile("res/miramar_rt.tga"); // ft
    _tex_dat[3].loadFromFile("res/miramar_bk.tga"); // rt
    _tex_dat[4].loadFromFile("res/miramar_dn.tga");
    _tex_dat[5].loadFromFile("res/miramar_up.tga");

    /*
    _tex_dat[0].loadFromFile("res/stormydays_lf.tga"); // bk
    _tex_dat[1].loadFromFile("res/stormydays_ft.tga"); // lf
    _tex_dat[2].loadFromFile("res/stormydays_rt.tga"); // ft
    _tex_dat[3].loadFromFile("res/stormydays_bk.tga"); // rt
    _tex_dat[4].loadFromFile("res/stormydays_dn.tga");
    _tex_dat[5].loadFromFile("res/stormydays_up.tga");
    */
}

void skybox_cleanup() {
    delete[] _tex_dat;
}

void skybox_draw(){
    // Store the current matrix
    glPushMatrix();

    // Reset and transform the matrix.
    glLoadIdentity();
    camera.applyNTranslations();

    // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);

    glScalef(-1.0, -1.0, -1.0);

    // Render the front quad
    sf::Texture::bind(&_tex_dat[0]);//glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the left quad
    sf::Texture::bind(&_tex_dat[1]);//glBindTexture(GL_TEXTURE_2D, _skybox[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glEnd();

    // Render the back quad
    sf::Texture::bind(&_tex_dat[2]); //glBindTexture(GL_TEXTURE_2D, _skybox[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );

    glEnd();

    // Render the right quad
    sf::Texture::bind(&_tex_dat[3]); //glBindTexture(GL_TEXTURE_2D, _skybox[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the top quad
    sf::Texture::bind(&_tex_dat[4]); //glBindTexture(GL_TEXTURE_2D, _skybox[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the bottom quad
    sf::Texture::bind(&_tex_dat[5]); //glBindTexture(GL_TEXTURE_2D, _skybox[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();

    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
}

