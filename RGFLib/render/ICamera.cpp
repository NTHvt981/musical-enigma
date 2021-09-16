#include "ICamera.h"

namespace rgf
{
std::shared_ptr<ICamera> ICamera::m_instance = NULL;

std::shared_ptr<ICamera> ICamera::GetInstance()
{
    return m_instance;
}

void ICamera::SetInstance(ICamera& camera)
{
    m_instance = std::make_shared<ICamera>(camera);
}

void ICamera::SetInstance(std::shared_ptr<ICamera> camera)
{
    m_instance = camera;
}

D3DXMATRIX ICamera::MirrorHorizontal(D3DXVECTOR3& vector)
{
    return D3DXMATRIX();
}

ICamera::ICamera(float w, float h, float s)
{
    this->m_width = w / s;
    this->m_height = h / s;
    this->m_scale = s;
    this->m_isOn = true;

    //width - 320, height - 240
    m_innerBound.left = m_width / 3;
    m_innerBound.top = m_height / 3;

    m_innerBound.right = m_width - m_innerBound.left;
    m_innerBound.bottom = m_height - m_innerBound.top;

    m_outerBound.bottom = m_outerBound.left = m_outerBound.right = m_outerBound.bottom = NULL;
}

void ICamera::SetMatrix()
{
    D3DXMatrixIdentity(&m_matrix);

    //matrix._22 = -1.0f;
    //matrix._41 = -position.x;

    m_matrix._22 = 1.0f;
    m_matrix._41 = m_position.x;
    m_matrix._42 = m_position.y;

    m_matrix = m_matrix * m_scale;
}

void ICamera::Transform(float x, float y, D3DXVECTOR3& new_pos)
{
    D3DXVECTOR3 old_pos(x, y, 0);
    D3DXVECTOR4 transform_vector_4;
    //D3DXVec3Transform(&transform_vector_4, &old_pos, &matrix);

    //new_pos.x = transform_vector_4.x;
    //new_pos.y = transform_vector_4.y;

    new_pos.x = x - m_position.x;
    new_pos.y = y - m_position.y;
}

void ICamera::Follow(float x, float y)
{
    m_position.x = x;
    m_position.y = y;

    if (m_position.x < m_outerBound.left)
        m_position.x = m_outerBound.left;
    if (m_position.x + m_width > m_outerBound.right)
        m_position.x = m_outerBound.right - m_width;

    if (m_position.y < m_outerBound.top)
        m_position.y = m_outerBound.top;
    if (m_position.y + m_height > m_outerBound.bottom)
        m_position.y = m_outerBound.bottom - m_height;
}

void ICamera::Follow(rgf::Vector pos)
{
    Follow(pos.x, pos.y);
}

void ICamera::FollowWithTransition(float x, float y)
{
    float _x = (x - m_width / 2) - m_position.x;
    float _y = (y - m_height / 2) - m_position.y;

    m_position.x += _x * 0.2;
    m_position.y += _y * 0.2;

    if (m_position.x < m_outerBound.left)
        m_position.x = m_outerBound.left;
    if (m_position.x + m_width > m_outerBound.right)
        m_position.x = m_outerBound.right - m_width;

    if (m_position.y < m_outerBound.top)
        m_position.y = m_outerBound.top;
    if (m_position.y + m_height > m_outerBound.bottom)
        m_position.y = m_outerBound.bottom - m_height;
}

void ICamera::FollowWithTransition(rgf::Vector pos)
{
}

void ICamera::FollowWithoutBound(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void ICamera::Move(float vx, float vy)
{
    m_position.x += vx;
    m_position.y += vy;
}

rgf::Vector ICamera::GetPosition()
{
    return m_position;
}

void ICamera::GetLTRB(float& l, float& t, float& r, float& b)
{
    l = m_position.x;
    t = m_position.y;
    r = m_position.x + m_width;
    b = m_position.y + m_height;
}

float ICamera::GetScale()
{
    return this->m_scale;
}

bool ICamera::IsOn()
{
    return m_isOn;
}

void ICamera::TurnOn()
{
    m_isOn = true;
}

void ICamera::TurnOff()
{
    m_isOn = false;
}

void ICamera::SetOuterBound(float l, float t, float r, float b)
{
    m_outerBound.left = l;
    m_outerBound.top = t;
    m_outerBound.right = r;
    m_outerBound.bottom = b;
}

void ICamera::GetOuterBound(float& l, float& t, float& r, float& b)
{
    l = m_outerBound.left;
    t = m_outerBound.top;
    r = m_outerBound.right;
    b = m_outerBound.bottom;
}

} //namespace rgf