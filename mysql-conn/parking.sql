-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 03 Cze 2012, 14:00
-- Wersja serwera: 5.5.16
-- Wersja PHP: 5.3.8

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
  `last_scan` int(11) unsigned NOT NULL DEFAULT '0',
  `threshold_high` double unsigned NOT NULL DEFAULT '100',
  `threshold_low` double unsigned NOT NULL DEFAULT '3',
  `threshold_scan` double unsigned NOT NULL DEFAULT '0.125',
  `apeture_size` int(11) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `parking_id` (`parking_id`),
  KEY `ostatni_skan` (`last_scan`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `camera`
--

INSERT INTO `camera` (`id`, `parking_id`, `address`, `type`, `last_scan`, `threshold_high`, `threshold_low`, `threshold_scan`, `apeture_size`) VALUES
(1, 1, 'C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/preview1.jpg', 'file', 0, 100, 3, 0.125, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `parking`
--

DROP TABLE IF EXISTS `parking`;
CREATE TABLE IF NOT EXISTS `parking` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `spots_count` int(11) unsigned NOT NULL DEFAULT '0',
  `free_spots` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `parking`
--

INSERT INTO `parking` (`id`, `spots_count`, `free_spots`) VALUES
(1, 100, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `spot`
--

DROP TABLE IF EXISTS `spot`;
CREATE TABLE IF NOT EXISTS `spot` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Zrzut danych tabeli `spot`
--

INSERT INTO `spot` (`id`, `camera_id`, `p1x`, `p1y`, `p2x`, `p2y`, `p3x`, `p3y`, `p4x`, `p4y`) VALUES
(1, 1, 516, 462, 548, 480, 493, 541, 461, 523),
(2, 1, 553, 483, 586, 502, 531, 564, 498, 545),
(3, 1, 457, 528, 498, 547, 433, 611, 401, 592),
(4, 1, 494, 550, 527, 569, 471, 633, 438, 614),
(5, 1, 217, 601, 249, 621, 192, 688, 160, 668),
(6, 1, 255, 623, 288, 643, 231, 711, 198, 691),
(7, 1, 293, 645, 326, 665, 269, 733, 236, 713);

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
SET FOREIGN_KEY_CHECKS=1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
