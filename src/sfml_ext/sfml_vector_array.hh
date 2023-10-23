#ifndef SFML_VECTOR_ARRAY_HH
#define SFML_VECTOR_ARRAY_HH



#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>









class VectorArray : public sf::Drawable
{
public:
  VectorArray();
  explicit VectorArray(sf::PrimitiveType type, std::size_t vertexCount = 0);

  std::size_t getVertexCount() const;
  std::size_t size() const;

  sf::Vertex& operator [](std::size_t index);
  const sf::Vertex& operator [](std::size_t index) const;

  void clear();
  void reserve(std::size_t);
  void resize(std::size_t);

  void push_back(const sf::Vertex&);
  void append(const sf::Vertex&);

  void setPrimitiveType(sf::PrimitiveType type);
  sf::PrimitiveType getPrimitiveType() const;

  std::vector<sf::Vertex> const & vertices() const;
  std::vector<sf::Vertex> & vertices();

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<sf::Vertex> m_vertices;
  sf::PrimitiveType       m_primitiveType;
};







#endif // SFML_VECTOR_ARRAY_HH