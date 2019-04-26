/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Pizza {
	public:
		Pizza(PizzaType type, PizzaSize size);
		~Pizza() = default;

        PizzaType getType() const noexcept;
        void setType(PizzaType type) noexcept;
        PizzaSize getSize() const noexcept;
        void setSize(PizzaSize size) noexcept;

	private:
        PizzaType _type;
        PizzaSize _size;
};

#endif /* !PIZZA_HPP_ */
