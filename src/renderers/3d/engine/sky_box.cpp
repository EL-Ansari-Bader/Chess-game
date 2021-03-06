#include "sky_box.h"

SkyBox::SkyBox() : Object() {
    mesh_cube_ = new Mesh(
            "./assets/models/cube.obj");

    Object::set_mesh(mesh_cube_);


    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

    for (auto &texture: faces_textures_)
        set_texture_face_(texture.first, texture.second);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Object::scale_ = glm::vec3(400.f);
    calculate_model_matrix_();

    glActiveTexture(0);
}

void SkyBox::set_texture_face_(GLuint type, const std::string &file_path) {
    int image_width = 0;
    int image_height = 0;
    unsigned char *image = SOIL_load_image(
            file_path.c_str(),
            &image_width,
            &image_height,
            nullptr,
            SOIL_LOAD_RGBA
    );

    if (!image)
        throw std::runtime_error("Texture loading failed");

    glTexImage2D(type, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);
}

void SkyBox::bind_texture_() {
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);
}


void SkyBox::unbind_texture_() {
    glActiveTexture(0);
}

void SkyBox::attach_to_shader(Shader *shader) {
    bind_texture_();

    shader->bind();
    shader_->set_uniform_1_i("sky_cube_texture", 5);
}

void SkyBox::draw() {
    bind_texture_();

    shader_->set_uniform_1_i("sky_box", 1);
    shader_->set_uniform_1_i("sky_cube_texture", 5);
    shader_->set_uniform_matrix_4_fv("model_matrix", model_matrix_);

    shader_->bind();
    mesh_->render();
    shader_->unbind();

    shader_->set_uniform_1_i("sky_box", 0);
    unbind_texture_();
}

SkyBox::~SkyBox() {
    delete mesh_cube_;

    glDeleteTextures(1, &texture_id_);
}
