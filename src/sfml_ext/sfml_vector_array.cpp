#include "sfml_vector_array.hh"




VectorArray::VectorArray()
: m_vertices()
, m_primitiveType(sf::Triangles)
{}

VectorArray::VectorArray(sf::PrimitiveType type, std::size_t vertexCount)
: m_vertices(vertexCount)
, m_primitiveType(type)
{}


std::size_t VectorArray::getVertexCount() const
{
	return (m_vertices.size());
}

std::size_t VectorArray::size() const
{
	return (m_vertices.size());
}


sf::Vertex& VectorArray::operator [](std::size_t index)
{
	return (m_vertices[index]);
}

const sf::Vertex& VectorArray::operator [](std::size_t index) const
{
	return (m_vertices[index]);
}


void VectorArray::clear()
{
	m_vertices.clear();
}

void VectorArray::reserve(std::size_t i)
{
	m_vertices.reserve(i);
}

void VectorArray::resize(std::size_t i)
{
	m_vertices.resize(i);
}


void VectorArray::push_back(const sf::Vertex & v)
{
	m_vertices.push_back(v);
}

void VectorArray::append(const sf::Vertex & v)
{
	m_vertices.push_back(v);
}


void VectorArray::setPrimitiveType(sf::PrimitiveType type)
{
	m_primitiveType = type;
}

sf::PrimitiveType VectorArray::getPrimitiveType() const
{
	return (m_primitiveType);
}


std::vector<sf::Vertex> const & VectorArray::vertices() const
{
	return (m_vertices);
}

std::vector<sf::Vertex> & VectorArray::vertices()
{
	return (m_vertices);
}


sf::Vertex const * VectorArray::data() const
{
	return (m_vertices.data());
}

sf::Vertex * VectorArray::data()
{
	return (m_vertices.data());
}


void VectorArray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_vertices.size())
		target.draw(m_vertices.data(), m_vertices.size(), m_primitiveType, states);
}

