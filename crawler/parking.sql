-- phpMyAdmin SQL Dump
-- version 3.5.0
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 09 Cze 2012, 13:43
-- Wersja serwera: 5.5.16
-- Wersja PHP: 5.4.0

SET FOREIGN_KEY_CHECKS=0;
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT=0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `parking`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `camera`
--

DROP TABLE IF EXISTS `camera`;
CREATE TABLE IF NOT EXISTS `camera` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `parking_id` int(11) unsigned NOT NULL,
  `address` varchar(255) NOT NULL,
  `type` varchar(255) NOT NULL DEFAULT 'file',
  `threshold_high` double unsigned NOT NULL DEFAULT '100',
  `threshold_low` double unsigned NOT NULL DEFAULT '33',
  `threshold_scan` double unsigned NOT NULL DEFAULT '0.125',
  `scale` double unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `parking_id` (`parking_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `camera`
--

INSERT INTO `camera` (`id`, `parking_id`, `address`, `type`, `threshold_high`, `threshold_low`, `threshold_scan`, `scale`) VALUES
(1, 1, 'C:\\Users\\tdrol\\Documents\\Visual Studio 2010\\Projects\\parking\\assets\\preview1.jpg', 'file', 100, 33, 0.125, 1),
(2, 2, 'C:\\Users\\tdrol\\Documents\\Visual Studio 2010\\Projects\\parking\\assets\\Parking-Lot.jpg', 'file', 100, 33, 0.1875, 1),
(3, 3, '../assets/transformers.jpg', 'file', 300, 125, 0.09725, 1),
(4, 4, '../assets/P3030027ParkingLot_wb.jpg', 'file', 200, 60, 0.125, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `parking`
--

DROP TABLE IF EXISTS `parking`;
CREATE TABLE IF NOT EXISTS `parking` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `last_scan` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `parking`
--

INSERT INTO `parking` (`id`, `last_scan`) VALUES
(1, 1339249235),
(2, 1339249235),
(3, 1339249236),
(4, 1339249237);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `spot`
--

DROP TABLE IF EXISTS `spot`;
CREATE TABLE IF NOT EXISTS `spot` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `status` smallint(1) unsigned NOT NULL DEFAULT '1',
  `camera_id` int(11) unsigned NOT NULL,
  `p1x` int(11) unsigned NOT NULL,
  `p1y` int(11) unsigned NOT NULL,
  `p2x` int(11) unsigned NOT NULL,
  `p2y` int(11) unsigned NOT NULL,
  `p3x` int(11) unsigned NOT NULL,
  `p3y` int(11) unsigned NOT NULL,
  `p4x` int(11) unsigned NOT NULL,
  `p4y` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `kamera_id` (`camera_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=41 ;

--
-- Zrzut danych tabeli `spot`
--

INSERT INTO `spot` (`id`, `status`, `camera_id`, `p1x`, `p1y`, `p2x`, `p2y`, `p3x`, `p3y`, `p4x`, `p4y`) VALUES
(1, 1, 1, 258, 231, 274, 240, 247, 271, 231, 262),
(2, 2, 1, 277, 242, 293, 251, 266, 282, 249, 273),
(3, 2, 1, 229, 264, 249, 274, 217, 306, 201, 296),
(4, 1, 1, 247, 275, 264, 285, 236, 317, 219, 307),
(5, 2, 1, 109, 301, 125, 311, 96, 344, 80, 334),
(6, 1, 1, 128, 312, 144, 322, 116, 356, 99, 346),
(7, 2, 1, 147, 323, 163, 333, 135, 367, 118, 357),
(8, 2, 2, 389, 326, 446, 343, 347, 393, 289, 370),
(9, 1, 2, 337, 309, 384, 324, 283, 368, 234, 348),
(10, 2, 2, 289, 294, 332, 307, 230, 346, 185, 328),
(11, 1, 2, 245, 280, 283, 291, 181, 326, 141, 311),
(12, 1, 2, 206, 268, 240, 278, 138, 309, 105, 296),
(13, 1, 2, 170, 257, 200, 266, 101, 294, 70, 282),
(14, 1, 2, 138, 248, 164, 256, 66, 280, 40, 271),
(15, 1, 3, 132, 149, 162, 173, 147, 184, 116, 159),
(16, 2, 3, 155, 134, 187, 157, 166, 171, 135, 147),
(17, 2, 3, 177, 121, 206, 145, 189, 156, 158, 133),
(18, 2, 3, 198, 109, 228, 129, 209, 142, 181, 119),
(19, 2, 3, 214, 98, 244, 118, 230, 127, 200, 107),
(20, 2, 3, 229, 90, 259, 108, 246, 117, 216, 97),
(21, 2, 3, 244, 81, 274, 99, 261, 107, 231, 89),
(22, 2, 3, 262, 70, 292, 87, 276, 97, 247, 80),
(23, 1, 3, 114, 160, 144, 186, 127, 198, 97, 170),
(24, 2, 3, 146, 188, 184, 220, 166, 233, 129, 199),
(25, 2, 3, 212, 144, 250, 166, 228, 183, 192, 157),
(26, 2, 3, 231, 131, 266, 154, 252, 164, 215, 142),
(27, 2, 3, 247, 120, 281, 143, 268, 152, 233, 129),
(28, 2, 3, 260, 110, 293, 133, 283, 141, 249, 118),
(29, 2, 3, 276, 100, 307, 122, 295, 132, 262, 109),
(30, 2, 3, 294, 88, 321, 110, 309, 120, 278, 99),
(31, 2, 3, 126, 201, 163, 235, 146, 248, 109, 214),
(32, 1, 3, 94, 171, 124, 199, 106, 211, 76, 183),
(33, 1, 4, 124, 439, 226, 480, 160, 489, 75, 444),
(34, 2, 4, 195, 431, 303, 465, 248, 475, 147, 438),
(35, 1, 4, 271, 419, 364, 451, 322, 461, 219, 427),
(36, 2, 4, 319, 408, 425, 435, 377, 444, 288, 415),
(37, 2, 4, 384, 396, 506, 427, 436, 432, 338, 406),
(38, 2, 4, 456, 513, 527, 499, 548, 577, 485, 594),
(39, 2, 4, 541, 495, 591, 480, 619, 555, 564, 573),
(40, 2, 4, 599, 475, 645, 462, 686, 534, 631, 551);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `stats_camera`
--

DROP TABLE IF EXISTS `stats_camera`;
CREATE TABLE IF NOT EXISTS `stats_camera` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `camera_id` int(11) unsigned NOT NULL,
  `stats_parking_id` int(11) unsigned NOT NULL,
  `free_spots` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `camera_id` (`camera_id`,`stats_parking_id`),
  KEY `stats_parking_id` (`stats_parking_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=53 ;

--
-- Zrzut danych tabeli `stats_camera`
--

INSERT INTO `stats_camera` (`id`, `camera_id`, `stats_parking_id`, `free_spots`) VALUES
(13, 1, 16, 3),
(14, 2, 17, 5),
(15, 1, 18, 3),
(16, 2, 19, 5),
(17, 1, 20, 3),
(18, 2, 21, 5),
(19, 1, 39, 3),
(20, 2, 40, 5),
(21, 1, 41, 3),
(22, 2, 42, 5),
(23, 1, 43, 3),
(24, 2, 44, 5),
(25, 1, 45, 3),
(26, 2, 46, 5),
(27, 1, 48, 3),
(28, 2, 49, 5),
(29, 1, 50, 3),
(30, 2, 51, 5),
(31, 1, 53, 3),
(32, 2, 54, 5),
(33, 1, 55, 3),
(34, 2, 56, 5),
(35, 1, 57, 3),
(36, 2, 58, 5),
(37, 1, 65, 3),
(38, 2, 66, 5),
(39, 1, 67, 3),
(40, 2, 68, 5),
(41, 1, 69, 3),
(42, 2, 70, 5),
(43, 1, 71, 3),
(44, 2, 72, 5),
(45, 3, 74, 3),
(46, 4, 75, 2),
(47, 1, 76, 3),
(48, 2, 77, 5),
(49, 1, 78, 3),
(50, 2, 79, 5),
(51, 3, 80, 3),
(52, 4, 81, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `stats_parking`
--

DROP TABLE IF EXISTS `stats_parking`;
CREATE TABLE IF NOT EXISTS `stats_parking` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `parking_id` int(11) unsigned NOT NULL,
  `free_spots` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `date` (`date`,`parking_id`),
  KEY `parking_id` (`parking_id`),
  KEY `free_spots` (`free_spots`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=82 ;

--
-- Zrzut danych tabeli `stats_parking`
--

INSERT INTO `stats_parking` (`id`, `date`, `parking_id`, `free_spots`) VALUES
(16, '2012-06-07 09:31:46', 1, 3),
(17, '2012-06-07 09:31:46', 2, 5),
(18, '2012-06-07 09:32:16', 1, 3),
(19, '2012-06-07 09:32:17', 2, 5),
(20, '2012-06-07 16:24:35', 1, 3),
(21, '2012-06-07 16:24:36', 2, 5),
(22, '2012-06-08 20:43:07', 1, 0),
(23, '2012-06-08 20:43:23', 1, 0),
(24, '2012-06-08 20:44:35', 1, 0),
(25, '2012-06-08 20:45:13', 1, 0),
(26, '2012-06-08 20:46:39', 1, 0),
(27, '2012-06-08 20:49:41', 1, 0),
(28, '2012-06-08 20:51:12', 1, 0),
(29, '2012-06-08 20:54:53', 1, 0),
(30, '2012-06-08 20:58:16', 1, 0),
(31, '2012-06-08 21:02:58', 1, 0),
(32, '2012-06-08 21:03:32', 1, 0),
(33, '2012-06-08 21:04:11', 1, 0),
(34, '2012-06-08 21:05:46', 1, 0),
(35, '2012-06-08 21:13:28', 1, 0),
(36, '2012-06-08 21:13:50', 1, 0),
(37, '2012-06-08 21:16:47', 1, 0),
(38, '2012-06-08 21:17:14', 1, 0),
(39, '2012-06-08 21:17:55', 1, 3),
(40, '2012-06-08 21:17:56', 2, 5),
(41, '2012-06-08 21:18:26', 1, 3),
(42, '2012-06-08 21:18:26', 2, 5),
(43, '2012-06-08 21:18:56', 1, 3),
(44, '2012-06-08 21:18:56', 2, 5),
(45, '2012-06-08 21:19:26', 1, 3),
(46, '2012-06-08 21:19:26', 2, 5),
(47, '2012-06-08 21:20:27', 1, 0),
(48, '2012-06-08 21:24:08', 1, 3),
(49, '2012-06-08 21:24:08', 2, 5),
(50, '2012-06-08 21:24:38', 1, 3),
(51, '2012-06-08 21:24:39', 2, 5),
(52, '2012-06-08 21:29:25', 1, 0),
(53, '2012-06-08 21:29:45', 1, 3),
(54, '2012-06-08 21:29:46', 2, 5),
(55, '2012-06-08 21:30:16', 1, 3),
(56, '2012-06-08 21:30:16', 2, 5),
(57, '2012-06-08 21:30:46', 1, 3),
(58, '2012-06-08 21:30:46', 2, 5),
(59, '2012-06-08 21:32:07', 1, 0),
(60, '2012-06-08 21:32:52', 1, 0),
(61, '2012-06-08 21:35:14', 1, 0),
(62, '2012-06-08 21:36:56', 1, 0),
(63, '2012-06-08 21:38:30', 1, 0),
(64, '2012-06-08 21:45:39', 1, 0),
(65, '2012-06-08 21:54:17', 1, 3),
(66, '2012-06-08 21:54:18', 2, 5),
(67, '2012-06-08 22:02:51', 1, 3),
(68, '2012-06-08 22:02:51', 2, 5),
(69, '2012-06-09 10:55:19', 1, 3),
(70, '2012-06-09 10:55:20', 2, 5),
(71, '2012-06-09 11:12:22', 1, 3),
(72, '2012-06-09 11:12:22', 2, 5),
(73, '2012-06-09 11:12:52', 1, 0),
(74, '2012-06-09 13:40:04', 3, 3),
(75, '2012-06-09 13:40:05', 4, 2),
(76, '2012-06-09 13:40:05', 1, 3),
(77, '2012-06-09 13:40:05', 2, 5),
(78, '2012-06-09 13:40:35', 1, 3),
(79, '2012-06-09 13:40:35', 2, 5),
(80, '2012-06-09 13:40:36', 3, 3),
(81, '2012-06-09 13:40:36', 4, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `stats_spot`
--

DROP TABLE IF EXISTS `stats_spot`;
CREATE TABLE IF NOT EXISTS `stats_spot` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `spot_id` int(11) unsigned NOT NULL,
  `status` enum('free','occupied','blocked') NOT NULL,
  `stats_camera_id` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `spot_id` (`spot_id`,`stats_camera_id`),
  KEY `stats_camera_id` (`stats_camera_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=382 ;

--
-- Zrzut danych tabeli `stats_spot`
--

INSERT INTO `stats_spot` (`id`, `spot_id`, `status`, `stats_camera_id`) VALUES
(78, 1, 'free', 13),
(79, 2, 'occupied', 13),
(80, 3, 'occupied', 13),
(81, 4, 'free', 13),
(82, 5, 'occupied', 13),
(83, 6, 'free', 13),
(84, 7, 'occupied', 13),
(85, 8, 'occupied', 14),
(86, 9, 'free', 14),
(87, 10, 'occupied', 14),
(88, 11, 'free', 14),
(89, 12, 'free', 14),
(90, 13, 'free', 14),
(91, 14, 'free', 14),
(92, 1, 'free', 15),
(93, 2, 'occupied', 15),
(94, 3, 'occupied', 15),
(95, 4, 'free', 15),
(96, 5, 'occupied', 15),
(97, 6, 'free', 15),
(98, 7, 'occupied', 15),
(99, 8, 'occupied', 16),
(100, 9, 'free', 16),
(101, 10, 'occupied', 16),
(102, 11, 'free', 16),
(103, 12, 'free', 16),
(104, 13, 'free', 16),
(105, 14, 'free', 16),
(106, 1, 'free', 17),
(107, 2, 'occupied', 17),
(108, 3, 'occupied', 17),
(109, 4, 'free', 17),
(110, 5, 'occupied', 17),
(111, 6, 'free', 17),
(112, 7, 'occupied', 17),
(113, 8, 'occupied', 18),
(114, 9, 'free', 18),
(115, 10, 'occupied', 18),
(116, 11, 'free', 18),
(117, 12, 'free', 18),
(118, 13, 'free', 18),
(119, 14, 'free', 18),
(120, 1, 'free', 19),
(121, 2, 'occupied', 19),
(122, 3, 'occupied', 19),
(123, 4, 'free', 19),
(124, 5, 'occupied', 19),
(125, 6, 'free', 19),
(126, 7, 'occupied', 19),
(127, 8, 'occupied', 20),
(128, 9, 'free', 20),
(129, 10, 'occupied', 20),
(130, 11, 'free', 20),
(131, 12, 'free', 20),
(132, 13, 'free', 20),
(133, 14, 'free', 20),
(134, 1, 'free', 21),
(135, 2, 'occupied', 21),
(136, 3, 'occupied', 21),
(137, 4, 'free', 21),
(138, 5, 'occupied', 21),
(139, 6, 'free', 21),
(140, 7, 'occupied', 21),
(141, 8, 'occupied', 22),
(142, 9, 'free', 22),
(143, 10, 'occupied', 22),
(144, 11, 'free', 22),
(145, 12, 'free', 22),
(146, 13, 'free', 22),
(147, 14, 'free', 22),
(148, 1, 'free', 23),
(149, 2, 'occupied', 23),
(150, 3, 'occupied', 23),
(151, 4, 'free', 23),
(152, 5, 'occupied', 23),
(153, 6, 'free', 23),
(154, 7, 'occupied', 23),
(155, 8, 'occupied', 24),
(156, 9, 'free', 24),
(157, 10, 'occupied', 24),
(158, 11, 'free', 24),
(159, 12, 'free', 24),
(160, 13, 'free', 24),
(161, 14, 'free', 24),
(162, 1, 'free', 25),
(163, 2, 'occupied', 25),
(164, 3, 'occupied', 25),
(165, 4, 'free', 25),
(166, 5, 'occupied', 25),
(167, 6, 'free', 25),
(168, 7, 'occupied', 25),
(169, 8, 'occupied', 26),
(170, 9, 'free', 26),
(171, 10, 'occupied', 26),
(172, 11, 'free', 26),
(173, 12, 'free', 26),
(174, 13, 'free', 26),
(175, 14, 'free', 26),
(176, 1, 'free', 27),
(177, 2, 'occupied', 27),
(178, 3, 'occupied', 27),
(179, 4, 'free', 27),
(180, 5, 'occupied', 27),
(181, 6, 'free', 27),
(182, 7, 'occupied', 27),
(183, 8, 'occupied', 28),
(184, 9, 'free', 28),
(185, 10, 'occupied', 28),
(186, 11, 'free', 28),
(187, 12, 'free', 28),
(188, 13, 'free', 28),
(189, 14, 'free', 28),
(190, 1, 'free', 29),
(191, 2, 'occupied', 29),
(192, 3, 'occupied', 29),
(193, 4, 'free', 29),
(194, 5, 'occupied', 29),
(195, 6, 'free', 29),
(196, 7, 'occupied', 29),
(197, 8, 'occupied', 30),
(198, 9, 'free', 30),
(199, 10, 'occupied', 30),
(200, 11, 'free', 30),
(201, 12, 'free', 30),
(202, 13, 'free', 30),
(203, 14, 'free', 30),
(204, 1, 'free', 31),
(205, 2, 'occupied', 31),
(206, 3, 'occupied', 31),
(207, 4, 'free', 31),
(208, 5, 'occupied', 31),
(209, 6, 'free', 31),
(210, 7, 'occupied', 31),
(211, 8, 'occupied', 32),
(212, 9, 'free', 32),
(213, 10, 'occupied', 32),
(214, 11, 'free', 32),
(215, 12, 'free', 32),
(216, 13, 'free', 32),
(217, 14, 'free', 32),
(218, 1, 'free', 33),
(219, 2, 'occupied', 33),
(220, 3, 'occupied', 33),
(221, 4, 'free', 33),
(222, 5, 'occupied', 33),
(223, 6, 'free', 33),
(224, 7, 'occupied', 33),
(225, 8, 'occupied', 34),
(226, 9, 'free', 34),
(227, 10, 'occupied', 34),
(228, 11, 'free', 34),
(229, 12, 'free', 34),
(230, 13, 'free', 34),
(231, 14, 'free', 34),
(232, 1, 'free', 35),
(233, 2, 'occupied', 35),
(234, 3, 'occupied', 35),
(235, 4, 'free', 35),
(236, 5, 'occupied', 35),
(237, 6, 'free', 35),
(238, 7, 'occupied', 35),
(239, 8, 'occupied', 36),
(240, 9, 'free', 36),
(241, 10, 'occupied', 36),
(242, 11, 'free', 36),
(243, 12, 'free', 36),
(244, 13, 'free', 36),
(245, 14, 'free', 36),
(246, 1, 'free', 37),
(247, 2, 'occupied', 37),
(248, 3, 'occupied', 37),
(249, 4, 'free', 37),
(250, 5, 'occupied', 37),
(251, 6, 'free', 37),
(252, 7, 'occupied', 37),
(253, 8, 'occupied', 38),
(254, 9, 'free', 38),
(255, 10, 'occupied', 38),
(256, 11, 'free', 38),
(257, 12, 'free', 38),
(258, 13, 'free', 38),
(259, 14, 'free', 38),
(260, 1, 'free', 39),
(261, 2, 'occupied', 39),
(262, 3, 'occupied', 39),
(263, 4, 'free', 39),
(264, 5, 'occupied', 39),
(265, 6, 'free', 39),
(266, 7, 'occupied', 39),
(267, 8, 'occupied', 40),
(268, 9, 'free', 40),
(269, 10, 'occupied', 40),
(270, 11, 'free', 40),
(271, 12, 'free', 40),
(272, 13, 'free', 40),
(273, 14, 'free', 40),
(274, 1, 'free', 41),
(275, 2, 'occupied', 41),
(276, 3, 'occupied', 41),
(277, 4, 'free', 41),
(278, 5, 'occupied', 41),
(279, 6, 'free', 41),
(280, 7, 'occupied', 41),
(281, 8, 'occupied', 42),
(282, 9, 'free', 42),
(283, 10, 'occupied', 42),
(284, 11, 'free', 42),
(285, 12, 'free', 42),
(286, 13, 'free', 42),
(287, 14, 'free', 42),
(288, 1, 'free', 43),
(289, 2, 'occupied', 43),
(290, 3, 'occupied', 43),
(291, 4, 'free', 43),
(292, 5, 'occupied', 43),
(293, 6, 'free', 43),
(294, 7, 'occupied', 43),
(295, 8, 'occupied', 44),
(296, 9, 'free', 44),
(297, 10, 'occupied', 44),
(298, 11, 'free', 44),
(299, 12, 'free', 44),
(300, 13, 'free', 44),
(301, 14, 'free', 44),
(302, 15, 'free', 45),
(303, 16, 'occupied', 45),
(304, 17, 'occupied', 45),
(305, 18, 'occupied', 45),
(306, 19, 'occupied', 45),
(307, 20, 'occupied', 45),
(308, 21, 'occupied', 45),
(309, 22, 'occupied', 45),
(310, 23, 'free', 45),
(311, 24, 'occupied', 45),
(312, 25, 'occupied', 45),
(313, 26, 'occupied', 45),
(314, 27, 'occupied', 45),
(315, 28, 'occupied', 45),
(316, 29, 'occupied', 45),
(317, 30, 'occupied', 45),
(318, 31, 'occupied', 45),
(319, 32, 'free', 45),
(320, 33, 'free', 46),
(321, 34, 'occupied', 46),
(322, 35, 'free', 46),
(323, 36, 'occupied', 46),
(324, 37, 'occupied', 46),
(325, 38, 'occupied', 46),
(326, 39, 'occupied', 46),
(327, 40, 'occupied', 46),
(328, 1, 'free', 47),
(329, 2, 'occupied', 47),
(330, 3, 'occupied', 47),
(331, 4, 'free', 47),
(332, 5, 'occupied', 47),
(333, 6, 'free', 47),
(334, 7, 'occupied', 47),
(335, 8, 'occupied', 48),
(336, 9, 'free', 48),
(337, 10, 'occupied', 48),
(338, 11, 'free', 48),
(339, 12, 'free', 48),
(340, 13, 'free', 48),
(341, 14, 'free', 48),
(342, 1, 'free', 49),
(343, 2, 'occupied', 49),
(344, 3, 'occupied', 49),
(345, 4, 'free', 49),
(346, 5, 'occupied', 49),
(347, 6, 'free', 49),
(348, 7, 'occupied', 49),
(349, 8, 'occupied', 50),
(350, 9, 'free', 50),
(351, 10, 'occupied', 50),
(352, 11, 'free', 50),
(353, 12, 'free', 50),
(354, 13, 'free', 50),
(355, 14, 'free', 50),
(356, 15, 'free', 51),
(357, 16, 'occupied', 51),
(358, 17, 'occupied', 51),
(359, 18, 'occupied', 51),
(360, 19, 'occupied', 51),
(361, 20, 'occupied', 51),
(362, 21, 'occupied', 51),
(363, 22, 'occupied', 51),
(364, 23, 'free', 51),
(365, 24, 'occupied', 51),
(366, 25, 'occupied', 51),
(367, 26, 'occupied', 51),
(368, 27, 'occupied', 51),
(369, 28, 'occupied', 51),
(370, 29, 'occupied', 51),
(371, 30, 'occupied', 51),
(372, 31, 'occupied', 51),
(373, 32, 'free', 51),
(374, 33, 'free', 52),
(375, 34, 'occupied', 52),
(376, 35, 'free', 52),
(377, 36, 'occupied', 52),
(378, 37, 'occupied', 52),
(379, 38, 'occupied', 52),
(380, 39, 'occupied', 52),
(381, 40, 'occupied', 52);

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `camera`
--
ALTER TABLE `camera`
  ADD CONSTRAINT `camera_ibfk_1` FOREIGN KEY (`parking_id`) REFERENCES `parking` (`id`) ON DELETE CASCADE;

--
-- Ograniczenia dla tabeli `spot`
--
ALTER TABLE `spot`
  ADD CONSTRAINT `spot_ibfk_1` FOREIGN KEY (`camera_id`) REFERENCES `camera` (`id`) ON DELETE CASCADE;

--
-- Ograniczenia dla tabeli `stats_camera`
--
ALTER TABLE `stats_camera`
  ADD CONSTRAINT `stats_camera_ibfk_1` FOREIGN KEY (`camera_id`) REFERENCES `camera` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `stats_camera_ibfk_2` FOREIGN KEY (`stats_parking_id`) REFERENCES `stats_parking` (`id`) ON DELETE CASCADE;

--
-- Ograniczenia dla tabeli `stats_parking`
--
ALTER TABLE `stats_parking`
  ADD CONSTRAINT `stats_parking_ibfk_1` FOREIGN KEY (`parking_id`) REFERENCES `parking` (`id`) ON DELETE CASCADE;

--
-- Ograniczenia dla tabeli `stats_spot`
--
ALTER TABLE `stats_spot`
  ADD CONSTRAINT `stats_spot_ibfk_1` FOREIGN KEY (`spot_id`) REFERENCES `spot` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `stats_spot_ibfk_2` FOREIGN KEY (`stats_camera_id`) REFERENCES `stats_camera` (`id`) ON DELETE CASCADE;
SET FOREIGN_KEY_CHECKS=1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
