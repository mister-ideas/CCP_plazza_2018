/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

class Reception {
	public:
		Reception(int multiplier, int numberOfCooks, int replaceTime);
		~Reception() = default;

        void launchShell() const;
        int getMultiplier() const noexcept;
        int getNumberOfCooks() const noexcept;
        int getReplaceTime() const noexcept;

	private:
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

#endif /* !RECEPTION_HPP_ */
