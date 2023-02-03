/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:00:04 by harndt            #+#    #+#             */
/*   Updated: 2023/02/03 16:23:04 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// =============================================================================
// EOF
// =============================================================================

# define EOC	"\033[0m"      // Text Reset

// =============================================================================
// REGULAR
// =============================================================================

# define BLACK	"\033[0;30m"        // Black
# define RED	"\033[0;31m"          // Red
# define GREEN	"\033[0;32m"        // Green
# define YELLOW	"\033[0;33m"       // Yellow
# define BLUE	"\033[0;34m"         // Blue
# define PURPLE	"\033[0;35m"       // Purple
# define CYAN	"\033[0;36m"         // Cyan
# define WHITE	"\033[0;37m"        // White

// =============================================================================
// BOLD
// =============================================================================

# define BBLACK		"\033[1;30m"       // Black
# define BRED		"\033[1;31m"         // Red
# define BGREEN		"\033[1;32m"       // Green
# define BYELLOW	"\033[1;33m"      // Yellow
# define BBLUE		"\033[1;34m"        // Blue
# define BPURPLE	"\033[1;35m"      // Purple
# define BCYAN		"\033[1;36m"        // Cyan
# define BWHITE		"\033[1;37m"       // White

// =============================================================================
// UNDERLINE
// =============================================================================

# define UBLACK		"\033[4;30m"       // Black
# define URED		"\033[4;31m"         // Red
# define UGREEN		"\033[4;32m"       // Green
# define UYELLOW	"\033[4;33m"      // Yellow
# define UBLUE		"\033[4;34m"        // Blue
# define UPURPLE	"\033[4;35m"      // Purple
# define UCYAN		"\033[4;36m"        // Cyan
# define UWHITE		"\033[4;37m"       // White

// =============================================================================
// BACKGROUND
// =============================================================================

# define BGBLACK	"\033[40m"       // Black
# define BGRED		"\033[41m"         // Red
# define BGGREEN	"\033[42m"       // Green
# define BGYELLOW	"\033[43m"      // Yellow
# define BGBLUE		"\033[44m"        // Blue
# define BGPURPLE	"\033[45m"      // Purple
# define BGCYAN		"\033[46m"        // Cyan
# define BGWHITE	"\033[47m"       // White

// =============================================================================
// HIGH INTENSITY
// =============================================================================

# define IBLACK		"\033[0;90m"       // Black
# define IRED		"\033[0;91m"         // Red
# define IGREEN		"\033[0;92m"       // Green
# define IYELLOW	"\033[0;93m"      // Yellow
# define IBLUE		"\033[0;94m"        // Blue
# define IPURPLE	"\033[0;95m"      // Purple
# define ICYAN		"\033[0;96m"        // Cyan
# define IWHITE		"\033[0;97m"       // White

// =============================================================================
// BOLD HIGH INTENSITY
// =============================================================================

# define BIBLACK	"\033[1;90m"      // Black
# define BIRED		"\033[1;91m"        // Red
# define BIGREEN	"\033[1;92m"      // Green
# define BIYELLOW	"\033[1;93m"     // Yellow
# define BIBLUE		"\033[1;94m"       // Blue
# define BIPURPLE	"\033[1;95m"     // Purple
# define BICYAN		"\033[1;96m"       // Cyan
# define BIWHITE	"\033[1;97m"      // White

// =============================================================================
// HIGH INTENSITY BACKGROUNDS
// =============================================================================
# define ONIBLACK	"\033[0;100m"   // Black
# define ONIRED		"\033[0;101m"     // Red
# define ONIGREEN	"\033[0;102m"   // Green
# define ONIYELLOW	"\033[0;103m"  // Yellow
# define ONIBLUE	"\033[0;104m"    // Blue
# define ONIPURPLE	"\033[0;105m"  // Purple
# define ONICYAN	"\033[0;106m"    // Cyan
# define ONIWHITE	"\033[0;107m"   // White

#endif