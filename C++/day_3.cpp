// https://adventofcode.com/2024/day/3
//
// clang++ -std=gnu++20 -stdlib=libc++ day_3.cpp -o day_3 && ./day_3 && rm day_3

#include <string>
#include <regex>
#include <cassert>
#include <iostream>
#include <cctype>

std::string raw_input();

[[maybe_unused]] int parse_input_data_with_regex(std::string const& input) {
  int res = 0;
  std::regex pattern{R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))"};
  std::sregex_iterator it{input.cbegin(), input.cend(), pattern};
  std::sregex_iterator end{};
  bool skip = false;
  for (; it != end; ++it) {
    auto const& match = *it;
    if (match.empty()) {
      continue;
    }

    if (match[0] == "don't()") {
      skip = true;
    } else if (match[0] == "do()") {
      skip = false;
    } else if (!skip) {
      res += std::stoi(match[1]) * std::stoi(match[2]);
    }
  }

  return res;
}

int parse_input_data(const std::string& input) {
  int res = 0;
  bool skip = false;
  size_t pos = 0;
  while (pos < input.size()) {
    if (skip && (input.size() - pos < 4 || input.compare(pos, 4, "do()") != 0)) {
      ++pos;
    } else if (input.compare(pos, 7, "don't()") == 0) {
      pos += 7;
      skip = true;
    } else if (input.compare(pos, 4, "do()") == 0) {
      pos += 4; // skip `do()`
      skip = false;
    } else if (input.compare(pos, 4, "mul(") == 0) {
      pos += 4; // skip `mul(`

      int x = 0;
      int digit_count = 0;
      while (pos < input.size() && std::isdigit(input[pos]) && digit_count < 3) {
        x = x * 10 + (input[pos] - '0');
        ++pos;
        ++digit_count;
      }

      if (digit_count == 0 || pos >= input.size() || input[pos] != ',') {
        continue;
      }

      ++pos; // skip `,`

      int y = 0;
      digit_count = 0;
      while (pos < input.size() && std::isdigit(input[pos]) && digit_count < 3) {
        y = y * 10 + (input[pos] - '0');
        ++pos;
        ++digit_count;
      }

      if (digit_count == 0 || pos >= input.size() || input[pos] != ')') {
        continue;
      }

      ++pos; // skip `)`

      if (!skip) {
        res += x * y;
      }
    } else {
      ++pos;
    }
  }

  return res;
}

int main() {
  int res = parse_input_data(raw_input());
  assert(res == 75920122);
  std::cout << "What do you get if you add up all of the results of the multiplications? " << res << std::endl;
}

std::string raw_input() {
  return R"(
where(536,162)~'what()what()how(220,399){ mul(5,253);mul(757,101)$where()@why()who()&when()from()mul(394,983)why()!&'how()mul(924,201)] mul(44,185)[]what()?${{}#,mul(116,356):~(from()]<why()mul(792,23)<+)%%'::mul(389,401)where()why()~{^@->when()'mul(557,491)<+select()]'mul(584,228)don't()*?#how()'where()&;@mul(58,115),where()?why()]]+:>mul(263,869)# %()from()[>mul(820,89);;#?when(),mul(553,296)where()(what()-mul(846,467){mul(436,71)}@$mul(553,611)do()where()<^select():+*'mul(411,428)-]?mul(722,379)}%'who(),>mul(471,731)*)+/what()@mul(729,484)/mul(672,572)'mul(375,937)who() ~how()%who()select()<mul(549,213)#/where()]mul(177,863)] {'],{'mul(486,207):+^select()mul(917,38) where()^why()@/-mul(255,420); ?mul(67,558)mul(141,261)(what()&{select()+mul(834,258)/>>;>don't(){mul(117,155)what()['why()}mul(946,797)why())^);where()%;}mul(387,438)'))mul(691,206)]when()+%>select()mul(182,238)how()' mul(522,434)where()mul(22,857)%mul(134,598)mul(689,301)-why()mul(7,725)^select()<,how()'%mul(632,167)}?*how()!mul(328,251)+mul(168,813)who()^when()why()mul(696,552)where()where()mul(177,527)%}$]%}from()]mul(600,612)select()&<&mul(5,789)<how()</)why()when()mul(935,875)where()+who()where()<&how()@mul(997,248)how()what()&who()^$]mul(59,285)mul(325,40)!#why(985,321);%mul(83,845)where()?$select()@(<(mul(463,456)>where()*/{who()why()do()*[when()}^]when()/mul(327,459)/&where()(mul(227,420)@(:[do()>mul(696,517)*mul(843,490)from(638,892)why()how()who()@mul(653,546)?how()when()^&]why()?mul(121,726)[where()-]}^?)>/mul(792,224)%+what()-/+mul(835,136)!{!'@)do()what()@#:*$*from()$mul(597,336)-?+^<']^]mul(222,657)('select()#!what()!mul(501,306):~+~@#'from()++mul(660,306)who()how();mul(884,257)why()when()what();:&$:!mul(180,820)]%who()-who()%(mul(770,324)~&]:?-mul(9,372 $)mul(987,378)from()select()where()mul(248,646)who(601,171)select()/>%[{$-mul(185,819) what() + :mul(442,907)--*)who()mul(541where(884,926)$mul(549,388)&^why(37,524)!?]!?from()don't()select(),%+ ?when(975,750)%}who()mul(262,401)<,/,from()mul(139,806)!;**);%+^;mul(76,978)'(what(){/mul!select()!mul(990,777)mul(188,545)(!what()/from()mul(272,32)from()^why()+#*mul(977,807):/^mul(266,744)select()from()*^<mul(800,207) /how()? ,mul(941,211),when()')mul(825,702),when()%~-;,?mul(883,307) where()%>select()!!,&who()mul(225,754)from()^#%^mul(513,969)why():mul(288,8)'who(331,621)@~~!@&mul(738,701)how()'@ where()don't(){>&>what()why()#(mul(744,683)@-from(498,125)when()don't()mul(773select()$mul(919,685)+where()mul(305,573)how()how(563,86)+,}who()~mul(291,852)%^from()mul(647,3)$+&:^-+/who()'mul(174,156){(mul(590select() -~*when()#^[mul(679,740)${;mul(463,30)$; (when()mul(875,270)who()/^#;~]!{mul(890(mul(224,108)#:!@mul <>^ where(),&<mul(486,524)who()who()#don't();)*-@:mul(452how()%-}*/where()*<@mul(613,459)where()}^'{mul(780,865)?;mul(365,535),%;,$how(),what()~]mul(622,700);don't()%who()who()mul(623,125)['how()} who()]don't()-where()!->who()^-$}mul(752,792)select() #/!how()@mul(213,376)(do()[why()%>?mul(771,799)^{&:/mul(382,131)how()^)}mul(412,25)?]]&^select()what()(mul(616,919)~}who()# ){who()when(263,342)^mul(946,363)
}?~who()select()-mul(316,505)&%*how()mul(363,589)>?%-:)where()~{{mul(38,452)select()%>[{]%>%mul(445,9)select()select()where()who(809,10)select()'&mul(505,640):>where()--mul(899,766)^where(){from()<mul(485,214)%]mul(469,95)$how(){why()+}mul(545,577)*why()who()from()@%who()$){mul(625,950)select()*mul(830,164)what()when()#!mul(530,4)don't()^mul(880,160)(?mul(508,717)$^why(14,313)when()~}who()mul(593,3)+mul(754,735)-#<(:}~{)mul(791,731)mul(718,434) [{$who()$'~select()how()mul%why(685,710)(/mul(458,943)select()/[[who()]/select()#%mul(454,66)+mul(521,460)/(when()+select(22,809){-'mul(206,53)when():)mul(420,119)+'%<mul(923,828)%~?mul(81,459)## ~*/!mul(266,160),-what()()}why()$(mul(634,181)mul(302,872)^@[when()}(#$*who()mul(831,161<@who()who()[;mul(947,843)/what()select()who()don't()~'@,'%;>@*mul(954,818)<{]$select(491,929)$mul(469,330);,'mul(709,381)>mul(692,607)select()(]/?don't()~from()what()<-&'[from()mul(20,147)who()&why()$(mul(482how(887,305)<&#how()!<[&/mul(964,713)~what(){what()^}}select()mul(37'**)]$what())mul(573,765)?where()#where()mul(861,190)what()what():~#?mul(149,843)<,-mul(705:^^~mul(134,719)})mul(22,371):}'<who()['{~[mul(672,177)}why()what()[+}how()mul(686!mul(484,84)(how()%(select()$%{select()#mul(857,111)mul<mul(11,521)$:mul(7,128)who()mul(614,497)why()when()]}from()how()!?do()mul(866,725)why()^^/+]%%mul(731,948)mul(33,176)when()]^-from()%mul(398,672)>when()how()}how()&do()-!mul(148,678)mul(801,30) what(),</^do()mul(510,36){^from()*<~(#}mul(283,696)mul(559,572)from()where()mul(762,321)*from()/mul(909,480)>mul&{?mul(184,545){}#select(448,839)+~+mul(986,322) what())/!<+mul(581,609)where()who()how()/mul(434,891))mul(728,525)[,'@@+mul(552,165);^:>)where() '?mul(23,400)mul(167,183)/*how() how()why()*mul(157,343)!?when()@;(~?mul(796,355)where()~<:$mul(312,781)<from()where()%who()mul(216,896)^+don't(),select()where(634,528)mul(9,285)]^why(508,561):who()(/]from()mul(718,986)]~]{^'*^mul(545,895)+what()%)%from()who()( %mul(722,572)select()+$,?&mul(107,209)$>{why()who()-:mul(440,283)select()how()how()mul(288,757)@how()mul(421,123)mul(589,921)how())?>) mul(455,905)-# who()mul(955,7-select();>when()mul(599,748):*!!##!>-(mul(273,990):{)!:mul(974,159)why(451,105)where()-$mul(696,260)~{ mul(216,455);when(912,287){mul(928,316)from()'#select()+who()> mul(890,212)[(why()/;mul(766,534)why()*>]select()why()from()from()mul(170,736)&when()#}mul(645,679))-where()$% mul(864,397)when()&%#mul(155,481))from()[-mul(160,707)mul(807,746)/where(779,210)mul(261,877)'[,$:what()mul(922,680)#what(972,646),how()where()%when()((why()mul(894,377)&]how()why(755,527)mul(48,266)(when()$what()mul(361,771)}select()[)mul(332,827)who()$^:)$>do()*;@[mul(690,51)?$mul(55,840)>[^,'#from()mul(863,343)@select()$mul(425,648)^why(208,282)mul(763,181)from()mul(794,818)+]''(^]mul(213,528):( ~'*^don't()!what()(mul(314,669)*,^!++!!,mul(641,237)](mul(440,591)}*mul(460,11)where()^*mul(708,915)</%<why()-mul(138,409)^&[?mul(275,464)
?>where(911,272)'mul(894,309)~+%@#}@#why()mul(330,296)what()mul(707,884)mul;&}<{>where()$why()]mul(609,787)*!/@who()+!,mul(342,89)::from()}#from()]:,/mul(102,723)select()^@when()who()mul(903,945)don't(),^)what()]mul(80,130)~+~[&@^,<mul(790,996)@]what(),<how()}(select()don't()why(){>from()<,mul(983,403);why()mul(936,199)&+:*who()@why()from():<mul]/$~/do(){what(),:%;%(;mul(502,753)-/from()(&mul(104,293),?)*mul(318,737)select()$%+>+~mul(402,74)!>how()}+mul(642,782)mul(714,667)+])mul(925,432,]~>mul(283,331)why()/*where()where()select()when()mul(243,952)/?{!!(mul(915,41);>(when()$#%mul(947,866)where()mul(221,297) select()>where()select()^$%mul(332,570)%]]mul(158,640)]don't()what(145,439)where() /-what()~ mul(800,255)mul(262,849)>}what()(how()why()^when()>mul(531,160)>(!;;from()mul(204,760)mul(513,132) ]why(657,793)[;>@[who()mul(884,112)-#/mul(29,581),when()[)'}:&mul(252,198)<<what()$['mul(919,291){select()select()]mul(239,410) do()mul(970,327)$when()-do()*!]&mul(851,279)select()how()where(){ #  'mul(159,479)} where()'-do()'select() !/who()select()'+{mul(692,852)who(105,599)??)mul(332,725)how(){mul(487,272)do()*:?why()-'mul(428,736)who(713,892)>select()?where()}$,~mul(814,493)!^where()?who() ][why()mul(654,203):&{]where()($[mul(635,667)%${}&$',mul(427,557) ~[{ %-mul(924,456)from(){^select()how()+mul(91,270)-<;>>don't()$?how()#<>{;mul(388how()?)mul(437,372),what()^/} !?when(423,466)-mul(413,767)+%!select()mul(404,30)]-,:when()when()mul(83,621)$mul(163,330)*when()!$?^^)${do()mul(836,70)how(146,272)*<-(+who(75,343)>}mul(326,92)]~())$(-!mul(377,382)mul(183,94)why()when()&from()don't();who()(? ?where()<<mul(908,788)who()-#[?mul(959,866)}>from()!;+?why()mul(766,106)how()*@;$mul(26,169)what()why()mul(407,336)select()mul(781,609)mul(567,131)%[when()<}mul(842,16)+(-~*}why(75,75)((mul(404,299)'];('select()&}(>mul(980,817),mul(759,27)when()$'mul(816,327)*&how()where()?*how(410,340)^mul(10,377)[mul#-<(+@mul(60,556)what()%;from() '%why()who()mul(71,194)]]@mul(54,618)when()['select()+(who()(~mul(615,986)] /how():+(&~mul(360,511)&how()don't()where()who()mul(387,887)?where()}#/what()what() mul(565,98)-!^?where()from(516,387)-}where()mul(852,909)~@where()%%why()}&-mul(964,784)#mul(351,184):)&mul(752,380)>mul(565,263));]mul(176,301)>^mul(724,532){how()~*,,{-mul(983,550){[select()>)mul(512}(]}-why()/why()mul(942,275),why()how()$;how()who()-?mul(111,602)where() ,)/{mul(647,51when()mul(752,155)]])]%/select()select(601,543)how(422,122)-mul(327,205)mul(108,233)select()how():do()},- when():mul(436,39)  ?>:why()when()how()<mul(10,524){:~do();{?where()mul(523,67)[@[}({who()$mul(167,645)mul(305,169)$how() why()^,when()))mul(940,645),$(mul(964,882)[]? <@>@?mul(544,861)]when()% mul(171,396)$who()@'mul(98,466)-why()+-~#mul(202,977)mul(65,156)what()mul(916,837)select()']?>*$'>}mul(248,949)}']%who()where(44,472)&;why()how(272,628)don't()%):,where()select()what()how()when()%mul(119,722)*when()/'[?mul(235,988):what()($?}$how()-mul(401,478)#:why()'{}what()#mul(760,203)<;#[:mul(594,881)%#<mul(401,886)what():,:&(who(130,871)how()%don't()mul(647,315)^who()when()(mul(146,838)where(){~when()when()when())) who()mul(578,112)'%what()}who()mul(949,792)
> (when()[where()/#!/usr/bin/perl,@;mul(794,217)select():'])select()mul(801,192)why()&]why()/:]*#mul(319,363^:]when()^?[when()do()!%!/:#^select()mul(189,908what():mul(439,753)~+>mul(889,297)$#-select()$mul(665,576)/@do()when()@@<*?mul(783,215)how()%what()where(259,619)(who()((mul(101,739)@from():,)?'who()-when()mul(935,345)why():,~:[;why();mul(344,351)#from()who()where()~)when()what()/mul(349,325)?%*~~-select()]mul(677,728)from()$mul(34,791)when()/what()(mul(162,982)%+!why()!how())when()mul(352,740))%when()why()mul(409,310)mul(969,23)what()when()(>[who()why() @mul(6,54)>-what()from(58,461)'mul(465,807)(mul(526,458)how()}{:;*[&mul(396,93)([]who()]*mul(719,44)?what()}mul(144[}&'#,where()mul(404,362)[$/who()^mul(402,634)-who()<what(),mul(620,339)$mul(261,803)*what()$;&&)mul(494what()#<<-mul(644,769)when()what()[]]^-^';mul+don't()$who()>+mul(210,882)~select(){+where()mul(113,5)/]mul(686,939)why()why()?$?where()mul(893,419)how()mul(522,816)why()'&];don't()mul(564,983)),mul(752,484)~}<how()~^where()?[*mul(84,307);^)]mul(486,387){$mul(437,187)-}(/where(189,211)+where()}mul(61,751)^*:mul(479,564)-+!,[)from()?@$mul(370,558)when(556,327)@when()what()@]%$~who()mul(79,777)]&(-,don't()[#?~mul(2,290)!'*^-don't()(#from()'mul(509,224){}+how()@ where()&mul(439,15)/do());&&^]select(130,812)mul>!from(),mul(794,228)mul(666,12)!>[who()why()%:mul(942,336),%^%don't()mul(974,403)}()<^{@ mul(34~?')+ ^where()what(438,775)mul(398,351)%;#<when()-~;where()mul(237,706)select()how(){;[+:who()-,mul(73,367)'<mul(258,509)[[?mul(734,571)select()?[mul(677,408);{;?,!~:select();mul(273,622))/^mul(213,14)^%*why()]select()-mul(785,933)mul(875,534)}mul(273,704)%where()*when():{::;[mul(403,147)/<$'!,;mul(575,503)?!{))[why()~$;mul(719,207)~*]why()mul(324,720)from())#;/}mul(553,685)how(332,401)!why()!mul(530,711){what(),])/!from()who(560,911)mul(952,650)&what()mul(987,390@what()*+^do()]what()]~&mul(92,809};from()&)^where()$^>*mul(608,425)-how();what(581,569)/}(where()mul(657,344)mul(952,983):mul(563,153))##~*<('who(910,367)mul(597,553)]) +}&/,mul(42,25)^-where()- {&?>mul(243,985)(where()what()mul(748,181)why()<*how()~ ]why()mul(513,836)^mul(528,931)^from()%mul(394,906)>&what()why()}select()mul(748,101)@{:mul(588,99)+^<]select()what()mul(762,499)*who()}mul(115,70)::$%>}mul(358,497)*$%how()mul(4from()>!]*>$)#how()from()don't()[{when()#where()why()where()why()mul(673,980)who(449,344)/@mul(632,452)from()where()*how()}?)][[mul(827,726)@~from()-mul(248,669)mul(745,698){mul(701<:how()what()mul(507,429)}when(638,137)mul(205,534)what(),{mul(98,543)do(),/*</;;<-;mul(47,166/from()~select()/$(mul(324,444))%[,],,mul(300@when(),why()where()how()why()(why()*@mul(504,369)*']%!mul(272,976);?}how()&]#from()'from()mul(380,961)mul(701,103)what()who()mul(57,637)!#when()'%{do()?*!from()<[>when()mul(242,591)#where()+mul(727,599);who()mul(127,428)'why()[';mul(731,342)%:$who()<what()]^mul(601,697){{%:[*mul(603,37)}?mul(937,728)[mul(305,102)?:who()@%^$mul(296,72)-!how()[select()]+%mul(132,763)mul(97,481)select()-mul(454,506)mul(814,106) !&}^^>what()$+do()*mul(739,211):'' !what()?,&]mul(87,206)+,who()>/&^~select(648,639)<mul(442,17)what()[-where()mul(452,266)why()how()#%[>!,mul(262,674)
,+who():mul(327,845)/ >@[>@}}mul(86,371)!~&&~how(79,334)mul(637,103)why()mul(358,845)-#~?why(243,672)select()+why()from()~mul(216,782)&mul(111,955)<?why()@ who()-^mul(791,328);how() %+]mul(946,620)why();+;how()~<]mul(623,64):<'<mul(986,415)#)[/(where()mul;*[({,-?#)#mul(38,403)^mul(91,193)who(573,63)select()'<!what() :why()mul(464,529)}(]>;what()~mul(677,376)select()when()mul(576,14)!}mul(70,850)^::select()what()mul(705,544)how(707,500)-where()how()what()mul(830,398)who()!do()mul(626,675)+where()<}who():mul(574,508)!;mul(306,829)&+)>what()@<{[~mul(795who()#*'where()who()?mul(548,420)*) %:when()when()mul(332,202)when()'where()^mul(72,648)]mul(866,929)mul(444,217}#mul(563,200)*select(581,639)!}who()/how()$mul(584,32)select(27,591)[#'mul(401,424)>,),mul(781&select()do()}what()#what()@what()<;mul(897,939)+where(),why()%mulhow()%where(203,705)mul(389,118)-what()select()&how())*@ <mul(146,178)%select()*why();mul(386,610)why()where()+why()?$how()mul(278[(where()who() (from()*[mul(178,632)@how()(mul(822,859)mul(774,887)!(} select()>$mul(316,546);]when()^-mul(730when()why()'+:*mul(433,570);-/]:select()(*#who()mul(12,582)[from()(how()!who()?)&,mul(474,681)mul(288,311)mul(281,240what()select()<when()<mul(934,466)%+%@where()^+{mul(628,780)how()@select()mul(813,147)!do()from(486,200)->{!mul(564,631)@'<[how()mul(972,373)mul(188,118)mul(630,960),/mul(105,916)how()#/mul(215,263)when():mul(257,474)[what()mul(565,99)*mul(195,386)[mul(695,513)from()#mulhow()mul(354,472)%-^when()%:}mul(420,822)]&mul(409,240)@where()!mul(65,591)mul(2,270)-]))from()mul(895,507){-what()^?#~ mul(13,268):why(919,274)]mul(37,808)}])why()+#+mul(19,585)from()how()%:$(where()mul(457,746)]mul(715,809)]+mul(542,65)@/):how(169,336)?when()~mul(871,498)]/{~~who()mul(438,984)what()from(289,777)/*}:*$%mul(176,297)&mul(404,56))mul(617,647)!when(){^what()why()}<^mul(412,110)where())#how()#;where()%&,mul(158,588) ~ from()'-^[select()mul(383,762)mul(215,479)%/:where()#[)who(567,411)mul(618,506)'from()}/how() )'~{mul(597,824)mul(130,88)when()-*how(891,580)mul(673,686);what()';,mul(404,486)-:when():&:$/??mul(335,183)/select()#why()what()who(396,219)mul(209,514)->)when()>;!>/from()mul(290,830) /what()~,mul(127,362)[%select()!mul(218,584)**}%'where()mul(806,757)when()>select()!why(343,900)(mul(416,926),&don't()#mul(140,136)(^mul(586,293)'from()~;)$mul(465,127)mul(50,37)select()from()how() )when()@/select()when()mul(268,549)~from()#)]why()^;?mul(928,48)where()&!mul(238,685)(/,mul(868,701)'* why()what()how()<%<-mul(147,775)(%%from();;mul(485,402){select()~,%]^mul(497,239)why()(mul(483,579)!mul(633,187)from(){how()'-[;$-mul(351,722)from()mul(376,405)mul(773,301)mul(714,478)&'&( mul(15,892)from()/when()}/^<who()'mul(7,951),from()'how()?*%don't()?$+what()#mul(430,674from()mul(503,262)]*,>;>#,mul(416,32)~?@(<what(984,491)@mul(97from()<<>*>'when():who()where()mul(550,92)mul(706,856){from()*from()mul(129,641)*from())where()mul(361,904)>why()mul(556,900)#/;,how()?mul(820,572)
where()#{*,!?:$mul(204,279)what()!{ what()mul(117,94)!select()>:mul(665,432)#don't()!!<!? mul(50,841)how()+~!]when(545,106)],%mul(69,679)how());how()#mul}$select()mul(29,553)when()+mul(242,498)?select(420,93)mul(879,710(mul(658,290)))+,-&mul(806,363)(#&]^+/?mul(462,199)mul(67,623)from()/{~^<}}when()mul(329,771);{]*#>]{mulwhen()'<how()]*what()>+{mul(533,772)why(708,386)mul(985,538)how()where()<%@;*mul(541,123)*/when()do()*@mul(689,5)]from()]~{@<[mul(624,102)how()*select()['?what()},;mul(689,339)when(),from()where()how(741,43)what()when()mul(976,335)$^mul(488,361)how()'?*$:don't()-/>%:why():from()+mul(273,731)?$?*what(312,921);{->mul(258,938)'mul(744,815)~!who()>[who()@(who()mul@select()when()&mul(244,475)@mul(642,298)'>when()+from()<{mul(73,293)do()what()}??when()from()mul(989,486)what()^mul(353,226)?%where()}]%,mul(452,316):~mul(156,967)?!mul(19,394)!,},when()<@mul-[</>>,mul(174,673):>#mul(874,712)from()])what(),'@how(667,413)(;mul(241,907)mul(320,563#{how()(mul(124,628)^!select()from(935,468)@when()when()<who(491,64)(mul(125,59)when()*!:where()why()~why()mul(804,677)where(307,856))]!*~mul(879,424)from():$''@;mul(884,639)*?[who()what()^$mul(734,624)?how(521,975)>-'how(466,423);mul(279,559)why()!$what(){:{why()from()mul(649,790);,?%&'/why()^&mul(534,924)>-!?when(){~$mul(158,17?#mul(968,123)what()who()>mul(250,420)mul(337,422)}(how()>-{*-  do()+(}~(,>who()mul(76,293);mul(293,210)*+?mul(438,928)]%~,%/#@[mul(183,794)+how() ;>}who()mul(332,416),why(801,76),+%don't())select(){where()what();-who()-mul(606,374)mul(534,560)$:~who()/ )%mul(51,112)%[<]<select()?<mul(471,577)who()!when(523,517)@%*{how()mul(52,512)mul(310,351);*!*what()-?#mul(617,189)^?when()/mul(936,553)& <':'&select()[mul(373,275)mul(892,327)++how(627,5)^&^'/@$mul(186,664)'why(672,157)?*?mul(878,211)%>;-(mul(713,297)how()mul(865,283)when()?[!;from()^%mul(852,418)mul(981,822)+&/{from()}{]what(134,416)when()mul(106,954)@who()>]why(){')&mul(638,435))! where(256,980)/from()?mul(742,736)mul(178,260)!select()do()!~mul(235,409)mul(4,876)&#:/how()how())mul(779,7)who()[]mul(257,563)who()from()mul(269,328):don't()^;?who()&how() mul(940,691)*'+how()%&mul(207,615)mul(22,730)}){;what(777,379)~who()~!mul(304,887)!$how()mul(897,888)?>*when()]/mul(28,168)when()+^:*}>mul(383,29)mul(467,873)@/-, <from(522,355)<^mul(670,942)])?^why()where()do()mul(152,343);$>]-from()%*mul(520,584)-how()(select()>^{$:<mul(585,847)select()how():'mul(205,503) }[why()mul(480,92)mul(439,908)?when()from()+[where()mul(190,679)#?@}<$mul(756,714) $*(!>(][-mul(866,764):[@,;?<mul(258,363)*>*}*@]when()mul(702,803)mul(417,62)from()-mul(405,512){)]/from()&mul(680,378)from()mul(272,215)-<when() how()}/mul(342,699):$mul(230,407)},~^what(),don't() what()mul(579,949)mul(32,967)why(833,463)^!when()[&-when()@mul(778,295)-where()why()]from()what() why()mul(872,242)where()~@?what()do():+/[when()'^mul(272,456)select()@@&[from()why()why()!mul(656,911)^mul(369,320)[%who(918,33)mul(430,762)don't()*,)>mul(678,155)]:why()who()@/how():@mul(327,946)!#when()+mul(484,853)!+?
)";
}
