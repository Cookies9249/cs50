# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Read teams into memory from file
    teams = []

    # Open ratings into file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        # When a 'team' (specified in .csv file) is found
        for team in reader:

            # Rating is converted into int
            team["rating"] = int(team["rating"])

            # Team is added as a dict into list
            teams.append(team)

    # Simulate N tournaments and keep track of win counts
    counts = {}

    # Initiate counts dict for every team
    for team in teams:
        teamName = team["team"]
        counts[teamName] = 0

    # Simulate tourney N times
    for i in range(N):
        winner = str(simulate_tournament(teams))

        # When a winner is declared, its score is increase
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # Repeats until winner is found
    while True:
        # Simulates round
        teams = simulate_round(teams)
        # If a winner is found
        if len(teams) == 1:
            # The name of the team is returned
            return teams[0]["team"]


if __name__ == "__main__":
    main()