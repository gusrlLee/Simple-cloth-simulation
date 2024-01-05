#include "Cloth.h"

Cloth::Cloth(int width, int height, float spacing, int startX, int startY, int startZ)
{

    int cloth_width = width;
    int cloth_height = height;
    m_spacing = spacing;

    m_point_cnt = cloth_width * cloth_height;
    m_curr_points = new glm::vec3[cloth_width * cloth_height];
    m_prev_points = new glm::vec3[cloth_width * cloth_height];

    float a = 0;
    float b = 0;
    for (int y = 0; y < cloth_height; y++)
    {
        for (int x = 0; x < cloth_width; x++)
        {
            //glm::vec3 point = glm::vec3(startX + x * spacing, startY, startZ + y * spacing);
            glm::vec3 point = glm::vec3(-2.0f + a, 2.0f, -2.0f + b);
            m_curr_points[y * cloth_width + x] = point;
            m_prev_points[y * cloth_width + x] = point;

            a += m_spacing;
        }
        b += m_spacing;
        a = 0;
    }

    for (int y = 0; y < cloth_height; y++)
    {
        for (int x = 0; x < cloth_width; x++)
        {
            int current_point_index = y * cloth_width + x;




            if (y != 0)
            {
                int up_point_index = (y-1) * cloth_width + x;

                sticks.push_back(std::make_pair(current_point_index, up_point_index));
            }

            if (x != 0)
            {
                int left_point_index = y * cloth_width + (x-1);
                sticks.push_back(std::make_pair(current_point_index, left_point_index));
            }
        }
    }

    m_stick_cnt = 2 * sticks.size();
    m_stick_points = new glm::vec3[m_stick_cnt];
}

Cloth::~Cloth()
{
    delete[] m_curr_points;
    delete[] m_prev_points;
    delete[] m_stick_points;
}

void Cloth::update(float delta_time)
{
    glm::vec3 acceleration = glm::vec3(gravity.x / particle_mass, gravity.y / particle_mass, gravity.z / particle_mass);
    for (int i=0; i<m_point_cnt; i++)
    {
        glm::vec3 prev_points = m_curr_points[i];
        m_curr_points[i].x = 2 * m_curr_points[i].x - m_prev_points[i].x + acceleration.x * (delta_time * delta_time);
        m_curr_points[i].y = 2 * m_curr_points[i].y - m_prev_points[i].y + acceleration.y * (delta_time * delta_time);
        m_curr_points[i].z = 2 * m_curr_points[i].z - m_prev_points[i].z + acceleration.z * (delta_time * delta_time);
        m_prev_points[i] = prev_points;
    }

    for (int i=0; i<m_point_cnt; i++)
    {
        checkCollision(m_curr_points[i]);
    }

    for (int i=0; i<sticks.size(); i++)
    {
        // get points
        glm::vec3 p0 = m_curr_points[sticks[i].first];
        glm::vec3 p1 = m_curr_points[sticks[i].second];
        
        glm::vec3 diff = p0 - p1;
        float diff_length = glm::length(p0 - p1);
        float diff_factor = (m_spacing - diff_length) / diff_length * 0.4f;
        glm::vec3 offset = diff * diff_factor;
        
        p0 += offset;
        p1 -= offset;

        m_curr_points[sticks[i].first] = p0;
        m_curr_points[sticks[i].second] = p1;

        m_stick_points[2 * i + 0] = p0;
        m_stick_points[2 * i + 1] = p1;
    }
}

void Cloth::draw(Shader &shader)
{
    shader.use();
    
    unsigned int vbo, stick_vbo;
    // draw points 
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &vbo);
    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, m_point_cnt * sizeof(glm::vec3), &m_curr_points[0], GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // glBindVertexArray(VAO);
    // glPointSize(3);
    // glDrawArrays(GL_POINTS, 0, m_point_cnt);

    // draw stick
    glGenVertexArrays(1, &stick_VAO);
    glGenBuffers(1, &stick_vbo);
    glBindVertexArray(stick_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, stick_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_stick_cnt * sizeof(glm::vec3), &m_stick_points[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(stick_VAO);
    glDrawArrays(GL_LINES, 0, m_stick_cnt);
}

void Cloth::checkCollision(glm::vec3 &p)
{
    glm::vec3 center = glm::vec3(0.0f);
    glm::vec3 v = p - center;
    float distance = glm::length(p - center);
    if (distance < 1) // collision! 
    {
        p = v / distance;
    }

}