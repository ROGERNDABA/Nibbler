/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeFLTK.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:17:30 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/22 09:41:08 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeFLTK.hpp"

SnakeFLTK::SnakeFLTK(int w, int h)
	: WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _score(0), _trackFood(0), _valBonus(false), _softExit(false), _start(0) {
	_start = clock();
	_display = NULL;
	TVertex tv;

	tv.x1 = (WINW / 2);
	tv.y1 = (WINH / 2);
	tv.x2 = tv.x1 + 15;
	tv.y2 = tv.y1 + 15;
	std::vector<TVertex>* tvt = new std::vector<TVertex>;
	tvt->push_back(tv);
	this->_key = new bool[4];
	std::fill(_key, _key + 4, false);
	_key[3] = true;
	this->_body = tvt;
	this->_obstacles = new std::vector<TVertex>;
	this->randFood();
	this->initObstacles();
	// this->init();
}

void SnakeFLTK::updateSnake(SnakeT Snake) {
	_start = 0;
	_softExit = 0;
	WINW = Snake.WINW;
	WINH = Snake.WINH;
	_body = Snake.body;
	_obstacles = Snake.obstacles;
	_food = Snake.food;
	_key = Snake.key;
	_prevKey = Snake.prevKey;
	_doExit = Snake.doExit;
	_speed = Snake.speed;
	_score = Snake.score;
	_bonus = Snake.bonus;
	_trackFood = Snake.trackFood;
	_valBonus = Snake.valBonus;
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(std::string exc) {
	this->_exc = "\033[31m" + exc + "\033[0m";
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(SnakeFLTK::SnakeFLTKException const& copy) {
	*this = copy;
}

const char* SnakeFLTK::SnakeFLTKException::what() const throw() {
	return (this->_exc.c_str());
}

SnakeFLTK::SnakeFLTKException& SnakeFLTK::SnakeFLTKException::operator=(SnakeFLTK::SnakeFLTKException const& rhs) {
	if (this != &rhs) {
	}
	return *this;
}

SnakeFLTK::~SnakeFLTK() {
	delete _body;
	delete _obstacles;
	if (_display) {
		_display->end();
		delete _display;
	}
}

SnakeFLTK::SnakeFLTK(SnakeFLTK const& copy) {
	*this = copy;
};

SnakeFLTK& SnakeFLTK::operator=(SnakeFLTK const& rhs) {
	if (this != &rhs) {
	}
	return *this;
}

void SnakeFLTK::init() {
	_display = new Fl_Window(WINW, WINH + 60, "Snake FLTK");
	if (!_display) {
		throw SnakeFLTKException("Could not init fltk display");
	}
	_display->color(FL_BLACK);
	_display->position(0, 0);
}

void SnakeFLTK::gameLoop() {
	std::vector<Fl_Box*> boxes;
	int prevEvent;
	std::vector<int> events;

	while (!_doExit && !_softExit) {
		_display->position(0, 0);
		int ev = Fl::event();

		if (ev == FL_SHORTCUT && prevEvent == 0) {
			int tmp;
			for (int i = 0; i < 4; i++) {
				if (_key[i])
					tmp = i;
			}
			switch (Fl::event_key()) {
				case FL_Up: {
					if (tmp != KEY_DOWN && tmp != KEY_UP) {
						_prevKey = tmp;
						std::fill(_key, _key + 4, false);
						_key[KEY_UP] = true;
					}
				} break;
				case FL_Down: {
					if (tmp != KEY_UP && tmp != KEY_DOWN) {
						_prevKey = tmp;
						std::fill(_key, _key + 4, false);
						_key[KEY_DOWN] = true;
					}
				} break;
				case FL_Left: {
					if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
						_prevKey = tmp;
						std::fill(_key, _key + 4, false);
						_key[KEY_LEFT] = true;
					}
				} break;
				case FL_Right: {
					if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
						_prevKey = tmp;
						std::fill(_key, _key + 4, false);
						_key[KEY_RIGHT] = true;
					}
				} break;
				case '1':
					_softExit = 1;
					break;
				case '2':
					_softExit = 2;
					break;
				case '3':
					_softExit = 3;
					break;
				case FL_Escape: {
					this->gameOver();
					_doExit = true, _softExit = 0;
				} break;
			}
			prevEvent = 1;
			ev = 0;
		}
		_now = clock();
		if (diffclock(_now, _start) >= (1.0 / _speed)) {
			_display->damage(FL_DAMAGE_ALL);
			_display->begin();
			ev = Fl::event();

			_display->color(FL_BLACK);

			if (checkFood()) {
				randFood();
				// al_play_sample(_sample, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				_score += _speed;
			}
			if (_key[KEY_UP]) {
				_doExit = moveHead(KEY_UP);
			} else if (_key[KEY_DOWN]) {
				_doExit = moveHead(KEY_DOWN);
			} else if (_key[KEY_LEFT]) {
				_doExit = moveHead(KEY_LEFT);
			} else if (_key[KEY_RIGHT]) {
				_doExit = moveHead(KEY_RIGHT);
			} else {
				_doExit = moveHead(-1);
			}
			boxes.push_back(new Fl_Box(0, 0, WINW, WINH + 60));
			boxes.back()->color(fl_rgb_color(236, 194, 255));
			boxes.back()->box(FL_FLAT_BOX);

			boxes.push_back(new Fl_Box(2, 60, WINW - 4, WINH - 2));
			boxes.back()->color(FL_BLACK);
			boxes.back()->box(FL_FLAT_BOX);

			std::stringstream ss;
			ss << _score;
			std::string s = "Score : " + ss.str();
			boxes.push_back(new Fl_Box(20, 35, 60, 20, s.c_str()));
			boxes.back()->box(FL_FLAT_BOX);
			boxes.back()->color(fl_rgb_color(236, 194, 255));
			boxes.back()->labelfont(FL_BOLD);
			boxes.back()->labelsize(18);

			boxes.push_back(new Fl_Box((WINW / 2) - 30, 5, 100, 25, "Snake FLTK"));
			boxes.back()->box(FL_FLAT_BOX);
			boxes.back()->color(fl_rgb_color(236, 194, 255));
			boxes.back()->labelfont(FL_BOLD);
			boxes.back()->labelsize(24);

			for (std::vector<TVertex>::iterator it = _obstacles->begin();
				 it != _obstacles->end(); ++it) {
				boxes.push_back(new Fl_Box(it->x1, it->y1, 14, 14));
				boxes.back()->color(fl_rgb_color(236, 194, 255));
				boxes.back()->box(FL_FLAT_BOX);
			}
			for (std::vector<TVertex>::iterator it = _body->begin(); it != _body->end(); ++it) {
				boxes.push_back(new Fl_Box(it->x1, it->y1, 14, 14));
				if (it == _body->begin()) {
					boxes.back()->color(fl_rgb_color(255, 0, 0));
					boxes.back()->box(FL_FLAT_BOX);
				} else {
					boxes.back()->color(fl_rgb_color(209, 102, 255));
					boxes.back()->box(FL_FLAT_BOX);
				}
			}
			boxes.push_back(new Fl_Box(_food.x1, _food.y1, 14, 14));
			boxes.back()->color(fl_rgb_color(0, 255, 0));
			boxes.back()->box(FL_FLAT_BOX);

			if (_valBonus) {
				boxes.push_back(new Fl_Box(_bonus.x1, _bonus.y1, 14, 14));
				boxes.back()->color(fl_rgb_color(0, 100, 255));
				boxes.back()->box(FL_FLAT_BOX);
			}
			_start = _now;
			prevEvent = 0;
			_display->show();
		}
		Fl::check();
		for (unsigned long i = 0; i < boxes.size(); i++)
			delete boxes[i];
		boxes.clear();
	}
	SNAKE.WINW = WINW;
	SNAKE.WINH = WINH;
	SNAKE.body = _body;
	SNAKE.obstacles = _obstacles;
	SNAKE.food = _food;
	SNAKE.key = _key;
	SNAKE.prevKey = _prevKey;
	SNAKE.doExit = _doExit;
	SNAKE.speed = _speed;
	SNAKE.score = _score;
	SNAKE.bonus = _bonus;
	SNAKE.trackFood = _trackFood;
	SNAKE.valBonus = _valBonus;
}

void SnakeFLTK::randFood() {
	int ranx = 1 + (std::rand() % ((WINW / 15) - 1)) - 1;
	int rany = 1 + (std::rand() % ((WINH / 15) - 1)) - 1;
	_food.x1 = ranx * 15;
	_food.x2 = _food.x1 + 15;
	_food.y1 = (rany * 15) + 60;
	_food.y2 = _food.y1 + 15;

	if (_valBonus && _trackFood % 5 == 0) {
		ranx = 1 + (std::rand() % ((WINW / 15) - 1)) - 1;
		rany = 1 + (std::rand() % ((WINH / 15) - 1)) - 1;
		_bonus.x1 = ranx * 15;
		_bonus.x2 = _bonus.x1 + 15;
		_bonus.y1 = (rany * 15) + 60;
		_bonus.y2 = _bonus.y1 + 15;
	}
	std::vector<TVertex>::iterator it;
	for (it = _obstacles->begin(); it != _obstacles->end(); ++it) {
		if (_food.x1 == it->x1 && _food.x2 == it->x2 && _food.y1 == it->y1 && _food.y2 == it->y2) {
			SnakeFLTK::randFood();
			return;
		} else if (_bonus.x1 == it->x1 && _bonus.x2 == it->x2 && _bonus.y1 == it->y1 && _bonus.y2 == it->y2) {
			SnakeFLTK::randFood();
			return;
		}
	}
}

bool SnakeFLTK::checkFood() {
	TVertex tmp = (*_body)[0];
	if (tmp.y1 == _food.y1 &&
		tmp.x1 == _food.x1 &&
		tmp.x2 == _food.x2 &&
		tmp.y2 == _food.y2) {
		_body->push_back(tmp);
		_trackFood++;
		if (_trackFood % 5 == 0) {
			_valBonus = true;
			_speed += 0.3;
		} else {
			_valBonus = false;
		}
		return true;
	} else if (tmp.y1 == _bonus.y1 &&
			   tmp.x1 == _bonus.x1 &&
			   tmp.x2 == _bonus.x2 &&
			   tmp.y2 == _bonus.y2) {
		_body->push_back(tmp);
		_body->push_back(tmp);
		_body->push_back(tmp);
		_speed += 0.5;
		_score += 20;
		_trackFood = 0;
		_valBonus = false;
	}
	return false;
}

bool SnakeFLTK::moveHead(int key) {
	TVertex head = *_body->begin();
	TVertex tail = head;
	switch (key) {
		case 0: {
			_body->pop_back();
			tail.y1 = head.y1 - 15;
			tail.y2 = head.y2 - 15;
			_body->insert(_body->begin(), tail);
		} break;
		case 1: {
			_body->pop_back();
			tail.y1 = head.y1 + 15;
			tail.y2 = head.y2 + 15;
			_body->insert(_body->begin(), tail);
		} break;
		case 2: {
			_body->pop_back();
			tail.x1 = head.x1 - 15;
			tail.x2 = head.x2 - 15;
			_body->insert(_body->begin(), tail);
		} break;
		case 3: {
			_body->pop_back();
			tail.x1 = head.x1 + 15;
			tail.x2 = head.x2 + 15;
			_body->insert(_body->begin(), tail);
		} break;
		default: {
			_body->pop_back();
			tail.x1 = head.x1 + 15;
			tail.x2 = head.x2 + 15;
			_body->insert(_body->begin(), tail);
		} break;
	}
	if (checkCollusion(tail)) {
		// al_play_sample(_sample2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		this->gameOver();
		return true;
	} else {
		return false;
	}
}

bool SnakeFLTK::checkCollusion(TVertex& tv) {
	std::vector<TVertex>::iterator it;
	for (it = _body->begin() + 1; it != _body->end(); ++it) {
		if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
			return true;
		}
	}
	for (it = _obstacles->begin(); it != _obstacles->end(); ++it) {
		if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
			return true;
		}
	}
	if (tv.x1 < 0 || tv.x2 > WINW || tv.y1 < 60 || tv.y2 > WINH + 60)
		return true;
	return false;
}

void SnakeFLTK::initObstacles() {
	TVertex tv;
	TVertex tv2;
	for (int i = 0; i < 10; i++) {
		int rx = 2 + (std::rand() % ((WINW / 15) - 2));
		while (rx >= (((WINW / 15) / 2) - 6) && rx <= (((WINW / 15) / 2) + 6)) {
			rx = 2 + (std::rand() % ((WINW / 15) - 2));
		}
		int ry = 2 + (std::rand() % ((WINH / 15) - 2));

		tv.x1 = rx * 15, tv.y1 = (ry * 15) + 60, tv.x2 = tv.x1 + 15, tv.y2 = tv.y1 + 15;

		tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1 + 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);

		tv2.x1 = tv.x2, tv2.y1 = tv.y1, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		tv2.x1 = tv.x2, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		tv2.x1 = tv.x2, tv2.y1 = tv.y1 + 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);

		tv2.x1 = tv.x1, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		tv2.x1 = tv.x1, tv2.y1 = tv.y2, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
		_obstacles->push_back(tv2);
		_obstacles->push_back(tv);
	}
}

void SnakeFLTK::gameOver() {
	clock_t start = clock();
	clock_t now = clock();
	std::vector<Fl_Box*> boxes;

	while (diffclock(now, start) <= 5) {
		_display->damage(FL_DAMAGE_ALL);
		_display->begin();

		_display->color(FL_BLACK);

		boxes.push_back(new Fl_Box((WINW / 2) - 100, (WINH / 2) - 120, 200, 90, "GAME OVER"));
		boxes.back()->box(FL_FLAT_BOX);
		boxes.back()->color(FL_BLACK);
		boxes.back()->labelcolor(FL_RED);
		boxes.back()->labelfont(FL_BOLD);
		boxes.back()->labelsize(60);

		std::stringstream ss;
		ss << _score;
		std::string s = "Score " + ss.str();
		boxes.push_back(new Fl_Box((WINW / 2) - 30, (WINH / 2), 60, 30, s.c_str()));
		boxes.back()->box(FL_FLAT_BOX);
		boxes.back()->color(FL_BLACK);
		boxes.back()->labelcolor(FL_WHITE);
		boxes.back()->labelfont(FL_BOLD);
		boxes.back()->labelsize(24);

		_display->show();

		now = clock();
		Fl::check();
		for (unsigned long i = 0; i < boxes.size(); i++)
			delete boxes[i];
		boxes.clear();
	}
}

SnakeT SnakeFLTK::getSnake() const {
	return this->SNAKE;
}

int SnakeFLTK::getEvent() const {
	return this->_softExit;
}

void SnakeFLTK::stop() {
	if (_display) {
		_display->end();
		Fl::delete_widget(_display);
		Fl::do_widget_deletion();
		Fl::clear_widget_pointer(_display);
		delete _display;
	}
	_display = NULL;
}

SnakeFLTK* createSnake(const int w, const int h) {
	return new SnakeFLTK(w, h);
}

void deleteSnake(SnakeFLTK* sa) {
	delete sa;
}

double diffclock(clock_t clock1, clock_t clock2) {
	double diffticks = clock1 - clock2;
	double diffms = (diffticks) / (CLOCKS_PER_SEC);
	return diffms;
}
