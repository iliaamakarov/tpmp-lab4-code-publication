-- Заполняем таблицы начальными данными

-- Члены экипажа
INSERT INTO CREW (surname, position, hire_date, birth_year) VALUES
('Иванов', 'captain', '2010-05-20', 1980),
('Петров', 'sailor', '2015-08-15', 1990),
('Сидоров', 'cook', '2018-01-10', 1995),
('Смирнов', 'sailor', '2020-03-12', 1998);

-- Пользователи
-- Пароль для всех 'password'. В реальном приложении пароли должны быть хешированы.
INSERT INTO USERS (username, password, role, crew_surname) VALUES
('captain', 'password', 'captain', 'Иванов'),
('crewman', 'password', 'crewman', 'Петров');

-- Траулеры
INSERT INTO TRAWLERS (name, displacement, construction_date) VALUES
('Морской Волк', 500, '2005-10-01'),
('Полярная Звезда', 750, '2012-06-15');

-- Инициализация статистики для траулеров
INSERT INTO TRAWLER_STATS (trawler_name, total_fish_caught) VALUES
('Морской Волк', 0),
('Полярная Звезда', 0);

-- Рейсы
INSERT INTO TRIPS (trawler_name, exit_date, return_date) VALUES
('Морской Волк', '2023-10-01', '2023-10-10'),
('Полярная Звезда', '2023-10-05', '2023-10-15'),
('Морской Волк', '2023-11-01', '2023-11-10');

-- Результаты рейсов (улов)
-- Рейс 1
INSERT INTO TRIP_RESULTS (trip_id, bank_name, fish_name, fish_quality, fish_quantity_kg) VALUES
(1, 'Северная', 'Треска', 'high', 500),
(1, 'Северная', 'Палтус', 'medium', 200),
(1, 'Западная', 'Окунь', 'low', 150);
-- Рейс 2
INSERT INTO TRIP_RESULTS (trip_id, bank_name, fish_name, fish_quality, fish_quantity_kg) VALUES
(2, 'Южная', 'Тунец', 'high', 1200),
(2, 'Южная', 'Скумбрия', 'low', 300);
-- Рейс 3
INSERT INTO TRIP_RESULTS (trip_id, bank_name, fish_name, fish_quality, fish_quantity_kg) VALUES
(3, 'Северная', 'Треска', 'high', 800),
(3, 'Восточная', 'Сельдь', 'medium', 400);
