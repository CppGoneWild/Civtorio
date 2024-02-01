




/*******************************************************************************
                    ____            __  __  ___
                   / __ \___  _____/ /_/  |/  /___ _____
                  / /_/ / _ \/ ___/ __/ /|_/ / __ `/ __ \
                 / _, _/  __/ /__/ /_/ /  / / /_/ / /_/ /
                /_/ |_|\___/\___/\__/_/  /_/\__,_/ .___/
                                                /_/
*******************************************************************************/









template <class T>
hex::RectMap<T>::RectMap(std::size_t height, std::size_t width, T const & def)
: m_data(height, line_t(width, def))
, m_max_coord(OffsetCoord(height, width))
, m_max_offset_coord(height, width)
{}



template <class T>
void hex::RectMap<T>::resize(std::size_t height, std::size_t width, T const & def)
{
	m_max_coord = Coord(OffsetCoord(height, width));
	m_max_offset_coord = OffsetCoord(height, width);

	m_data.resize(height);
	for (auto it = m_data.begin(); it != m_data.end(); ++it)
		it->resize(width, def);
}



template <class T>
std::size_t hex::RectMap<T>::height() const
{
	return (m_max_offset_coord.row());
}

template <class T>
std::size_t hex::RectMap<T>::width() const
{
	return (m_max_offset_coord.col());
}




template <class T>
bool hex::RectMap<T>::is_in_bound(Coord const & c) const
{
	return (is_in_bound(OffsetCoord(c)));
}

template <class T>
bool hex::RectMap<T>::is_in_bound(OffsetCoord const & c) const
{
	return (c.row() >= 0 && c.col() >= 0 &&
	        c.row() < m_max_offset_coord.row() &&
	        c.col() < m_max_offset_coord.col());
}



template <class T>
T const & hex::RectMap<T>::operator[](Coord const & c) const
{
	return ((*this)[OffsetCoord(c)]);
}

template <class T>
T const & hex::RectMap<T>::operator[](OffsetCoord const & c) const
{
	return (m_data[c.row()][c.col()]);
}



template <class T>
T & hex::RectMap<T>::operator[](Coord const & c)
{
	return ((*this)[OffsetCoord(c)]);
}

template <class T>
T & hex::RectMap<T>::operator[](OffsetCoord const & c)
{
	return (m_data[c.row()][c.col()]);
}












/*******************************************************************************
                 _       __
                | |     / /________ _____  ____  ___  _____
                | | /| / / ___/ __ `/ __ \/ __ \/ _ \/ ___/
                | |/ |/ / /  / /_/ / /_/ / /_/ /  __/ /
                |__/|__/_/   \__,_/ .___/ .___/\___/_/
                                 /_/   /_/
*******************************************************************************/





template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, OffsetCoord & coord) const
{
	OffsetCoord result;

	bool ret = wrap(map, coord, result);
	if (ret)
		coord = result;

	return (ret);
}

template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, OffsetCoord const & coord, OffsetCoord & result) const
{
	int wrapped_col = coord.col();
	int wrapped_row = coord.row();

	if (m_wrap_horizontaly)
		wrapped_col %= map.width();
	if (m_wrap_verticaly)
		wrapped_row %= map.height();

	result = OffsetCoord(wrapped_col, wrapped_row);

	return (map.is_in_bound(coord));
}


template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, Coord const & coord, Coord & result) const
{
	OffsetCoord tmp;
	bool ret = wrap(map, OffsetCoord(coord), tmp);
	result = Coord(tmp);
	return (ret);
}

template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, Coord const & coord, OffsetCoord & result) const
{
	return (wrap(map, OffsetCoord(coord), result));
}
