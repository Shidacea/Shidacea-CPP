#pragma once

#include "MrbWrap.h"
#include "Shape.h"

#include <array>

#include <SFML/Graphics.hpp>

//! Point and Line do not work yet for drawing

class PointShape : public sf::Shape {

public:

	explicit PointShape(const sf::Vector2f& point = sf::Vector2f()) {

		m_point = point;

		update();

	}

	void setPoint(const sf::Vector2f& value) {

		m_point = value;

		update();

	}

	virtual std::size_t getPointCount() const {

		return 1;

	}

	virtual sf::Vector2f getPoint(std::size_t index) const {

		return m_point;

	}

private:

	sf::Vector2f m_point;

};

class LineShape : public sf::Shape {

public:

	explicit LineShape(const sf::Vector2f& start_point = sf::Vector2f(),
		const sf::Vector2f& end_point = sf::Vector2f()) {

		m_points[0] = start_point;
		m_points[1] = end_point;

		update();

	}

	void setStartPoint(const sf::Vector2f& value) {

		m_points[0] = value;
		
		update();

	}

	void setEndPoint(const sf::Vector2f& value) {

		m_points[1] = value;

		update();

	}

	virtual std::size_t getPointCount() const {

		return 2;

	}

	virtual sf::Vector2f getPoint(std::size_t index) const {

		return m_points[index];

	}

private:

	std::array<sf::Vector2f, 2> m_points;

};

class TriangleShape : public sf::Shape {

public:
	
	explicit TriangleShape(const sf::Vector2f& point_0 = sf::Vector2f(), 
		const sf::Vector2f& point_1 = sf::Vector2f(), 
		const sf::Vector2f& point_2 = sf::Vector2f()) {

		m_edge_points[0] = point_0;
		m_edge_points[1] = point_1;
		m_edge_points[2] = point_2;

		update();

	}

	void setPoint(std::size_t index, const sf::Vector2f& value) {

		m_edge_points[index] = value;

		update();

	}

	virtual std::size_t getPointCount() const {

		return 3;

	}

	virtual sf::Vector2f getPoint(std::size_t index) const {

		return m_edge_points[index];

	}

private:

	std::array<sf::Vector2f, 3> m_edge_points;


};

void setup_ruby_class_draw_shape(mrb_state* mrb, RClass* ruby_module);