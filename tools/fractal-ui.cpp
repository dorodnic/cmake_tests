#include <GLFW/glfw3.h>
#include <fractal/fractal.h>

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#include <iostream>
#include <vector>

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Fractal UI", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    
    double selected_x[2];
    double selected_y[2];
    int left_status = GLFW_RELEASE;
    int right_status = GLFW_RELEASE;
    
    double x_coords[2] = { -2.f, 1.f };
    double y_coords[2] = { -1.5f, 1.5f };
    
    int state = 0;
    
    std::vector<uint8_t> image;
    
    uint32_t texture_handle;
    glGenTextures(1, &texture_handle);
    
    while (!glfwWindowShouldClose(window))
    {        
        glClear(GL_COLOR_BUFFER_BIT);

        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        glViewport(0, 0, fb_width, fb_height);
        
	int w, h;
	glfwGetWindowSize(window, &w, &h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.f, fb_width, 0.f, fb_height, 0.f, 1.f);
        
        auto new_size = fb_width * fb_height;
        if (image.size() != new_size)
        {
            image.resize(new_size);
            std::vector<double> xs; xs.resize(new_size);
            std::vector<double> ys; ys.resize(new_size);
            std::vector<int> res; res.resize(new_size);
            for (int j = 0; j < fb_height; j++)
            {
                for (int i = 0; i < fb_width; i++)
                {
                    auto t = x_coords[0] + (x_coords[1] - x_coords[0]) * i / (float)fb_width;
                    auto s = y_coords[0] + (y_coords[1] - y_coords[0]) * j / (float)fb_height;
                    xs[fb_width * j + i] = t;
                    ys[fb_width * j + i] = s;
                }
            }
            fractal_mandelbrot_bulk(xs.data(), ys.data(), new_size, res.data(), 254);
            for (int i = 0; i < new_size; i++) image[i] = res[i];
            glBindTexture(GL_TEXTURE_2D, texture_handle);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb_width, fb_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        
        auto curr_right_status = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        if (curr_right_status != right_status)
        {
            right_status = curr_right_status;
            if (curr_right_status == GLFW_RELEASE)
                state = 0;
        }
        
        auto curr_left_status = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (curr_left_status != left_status)
        {
            left_status = curr_left_status;
            if (curr_left_status == GLFW_RELEASE)
            {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                selected_x[state] = x;
                selected_y[state] = h - y;

                state = (state + 1) % 2;
                
                if (state == 0)
                {
                    auto x0 = std::min(selected_x[0], selected_x[1]);
                    auto x1 = std::max(selected_x[0], selected_x[1]);
                    auto y0 = std::min(selected_y[0], selected_y[1]);
                    auto y1 = std::max(selected_y[0], selected_y[1]);
                    
                    auto ar = (float)h / w;
        
                    auto t0 = x_coords[0] + (x_coords[1] - x_coords[0]) * x0 / (float)w;
                    auto s0 = y_coords[0] + (y_coords[1] - y_coords[0]) * y0 / (float)h;
                    auto t1 = x_coords[0] + (x_coords[1] - x_coords[0]) * x1 / (float)w;
                    auto s1 = y_coords[0] + (y_coords[1] - y_coords[0]) * y1 / (float)h;
                    
                    auto sm = (s1 + s0) * 0.5;
                    auto tw = t1 - t0;
                    auto sh = tw * ar;
                    
                    x_coords[0] = t0; x_coords[1] = t1;
                    y_coords[0] = sm - sh * 0.5; y_coords[1] = sm + sh * 0.5;
                    image.resize(0);
                }
            }
        }
        
        if (state == 1)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            selected_x[state] = x;
            selected_y[state] = h - y;
        }
        
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0.f, 1.f); glVertex2f(0.f, fb_height);
        glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
        glTexCoord2f(1.f, 1.f); glVertex2f(fb_width, fb_height);
        glTexCoord2f(1.f, 0.f); glVertex2f(fb_width, 0.f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        if (state >= 1)
        {
            auto x0 = std::min(selected_x[0], selected_x[1]);
            auto x1 = std::max(selected_x[0], selected_x[1]);
            auto y0 = std::min(selected_y[0], selected_y[1]);
            auto y1 = std::max(selected_y[0], selected_y[1]);
            
            auto fx = fb_width / (double)w;
            auto fy = fb_height / (double)h;

            glColor3f(1.f, 1.f, 1.f);
            glBegin(GL_LINE_STRIP);
                glVertex2f(x0 * fx, y0 * fy);
                glVertex2f(x1 * fx, y0 * fy);
                glVertex2f(x1 * fx, y1 * fy);
                glVertex2f(x0 * fx, y1 * fy);
                glVertex2f(x0 * fx, y0 * fy);
            glEnd();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);

    exit(EXIT_SUCCESS);
}
