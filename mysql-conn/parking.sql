-- phpMyAdmin SQL Dump
-- version 3.5.0
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 06 Cze 2012, 17:59
-- Wersja serwera: 5.5.16
-- Wersja PHP: 5.4.0

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Zrzut danych tabeli `camera`
--

INSERT INTO `camera` (`id`, `parking_id`, `address`, `type`, `threshold_high`, `threshold_low`, `threshold_scan`, `scale`) VALUES
(1, 1, 'C:\\Users\\tdrol\\Documents\\Visual Studio 2010\\Projects\\parking\\assets\\preview1.jpg', 'file', 100, 33, 0.125, 1),
(2, 2, 'C:\\Users\\tdrol\\Documents\\Visual Studio 2010\\Projects\\parking\\assets\\Parking-Lot.jpg', 'file', 100, 33, 0.1875, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `parking`
--

DROP TABLE IF EXISTS `parking`;
CREATE TABLE IF NOT EXISTS `parking` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `last_scan` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Zrzut danych tabeli `parking`
--

INSERT INTO `parking` (`id`, `last_scan`) VALUES
(1, 1339004649),
(2, 1339004649);

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=15 ;

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
(14, 1, 2, 138, 248, 164, 256, 66, 280, 40, 271);

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=78 ;

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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
