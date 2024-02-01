#ifndef SFML_VECTOR_ARRAY_HH
#define SFML_VECTOR_ARRAY_HH



#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>








/** This class is an upgrade of sf::VertexArray.
 * 
 * In addition to all behavior of sf::VertexArray,
 * you can use some of std::vector capacities such as
 * reserve, resize and access underlying container.
 */
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

  sf::Vertex const * data() const;
  sf::Vertex * data();

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<sf::Vertex> m_vertices;
  sf::PrimitiveType       m_primitiveType;
};







#endif // SFML_VECTOR_ARRAY_HH