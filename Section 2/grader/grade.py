import json

PRINT_ORDER = ['Question 1', 
               'Question 2', 
               'Question 3', 
               'Question 4', 
               'Question 5',
               'Question 6',
               'Question 7']

SCORES = {
    'Question 1': {
        'description': 'Resultats de la question 1',
        'test unitaire': {
            'description': 'Le calcul du numero de page est correct',
            #'granted': False,
            'scale': 1.0,
            'score': 0
        }
    },
    'Question 2': {
        'description': 'Resultats de la question 2',
        'test unitaire': {
            'description': 'Le calcul du deplacement dans la page est correct',
            # 'granted': False,
            'scale': 1.0,
            'score': 0
        }
    },
    'Question 3': {
        'description': 'Resultats de la question 3',
        'test unitaire': {
            'description': 'Le calcul de l\'adresse est correct',
            # 'granted': False,
            'scale': 1.0,
            'score': 0
        }
    },
    'Question 4': {
        'description': 'Resultats de la question 4',
        'recherche dans le TLB': {
            'description': 'La recherche dans le TLB fonctionne',
            'score': 0,
            'scale': 3.0
        }
    },
    'Question 5': {
        'description': 'Resultats de la question 5',
        'recherche dans la table des pages': {
            'description': 'La recherche dans la table des pages fonctionne',
            #'granted': False,
            'scale': 3.0,
            'score': 0
        }
    },
    'Question 6': {
        'description': 'Resultats de la question 6',
        'mise a jour de la memoire': {
            'description': 'La mise a jour de la memoire fonctionne',
            'score': 0,
            'scale': 3.0
        }
    },
    'Question 7': {
        'description': 'Resultats de la question 7',
        'mise a jour du TLB': {
            'description': 'La mise a jour du TLB fonctionne',
            'score': 0,
            'scale': 4.0
        }
    }
}

def isQuestion1(line):
    return line.find('numero de page') > -1

def isQuestion2(line):
    return line.find('deplacement dans la page') > -1

def isQuestion3(line):
    return line.find('adresse complete') > -1

def isQuestion4(line):
    return line.find('Recherche du TLB') > -1

def isQuestion5(line):
    return line.find('Recherche dans la table des pages') > -1

def isQuestion6(line):
    return line.find('Ajout dans la memoire') > -1

def isQuestion7(line):
    return line.find('Sommaire mise a jour TLB') > -1

def isSimpleQuestionPassed(score, expected):
    return score == expected

def getQuestionResultFromLine(line):
    return line.split(':').pop().split('/')[0].replace(" ", '')

def interpretResults(resultLines):
    graded = [False, False, False, False, False, False, False]
    for line in resultLines:
        if isQuestion1(line) and not graded[0]:
            SCORES['Question 1']['test unitaire']['score'] = float(getQuestionResultFromLine(line))
            graded[0] = True
            print("score for question 1")
            continue
        if isQuestion2(line) and not graded[1]:
            SCORES['Question 2']['test unitaire']['score'] = float(getQuestionResultFromLine(line))
            graded[1] = True
            continue
        if isQuestion3(line) and not graded[2]:
            SCORES['Question 3']['test unitaire']['score'] = float(getQuestionResultFromLine(line))
            graded[2] = True
            continue
        if isQuestion4(line) and not graded[3]:
            SCORES['Question 4']['recherche dans le TLB']['score'] = float(getQuestionResultFromLine(line))
            graded[3] = True
            continue
        if isQuestion5(line) and not graded[4]:
            SCORES['Question 5']['recherche dans la table des pages']['score'] = float(getQuestionResultFromLine(line))
            graded[4] = True
            continue
        if isQuestion6(line) and not graded[5]:
            SCORES['Question 6']['mise a jour de la memoire']['score'] = float(getQuestionResultFromLine(line))
            graded[5] = True
            continue
        if isQuestion7(line) and not graded[6]:
            SCORES['Question 7']['mise a jour du TLB']['score'] = float(getQuestionResultFromLine(line))
            graded[6] = True
            continue

    print("--------------------")
    print("Memoire Lab: Autograder")
    print("--------------------")
    print("")

    totalScore = 0
    totalScale = 0
    bonusScore = 0
    bonusScale = 0
    scoresJSON = {
        'scores': {}
    }
    
    for problem in PRINT_ORDER:
        obj = SCORES[problem]
        print(obj['description'])
        print("------------------------------------------------------------------------------")
        
        totalProblemScore = 0
        totalProblemScale = 0
        bonusProblemScore = 0
        bonusProblemScale = 0
        problemInvalidated = False
        for key, subscores in obj.items():
            if key  == 'description':
                continue
            
            if 'granted' in subscores:
                subscore = subscores['scale'] if subscores['granted'] else 0.0
            elif 'score' in subscores:
                # Round score
                subscores['score'] = round(subscores['score'] * 100) / 100
                subscore = subscores['score']
            elif 'passed' in subscores:
                if not subscores['passed']:
                    problemInvalidated = True
            else:
                subscore = 0
            if 'passed' in subscores:
                if subscores['passed']:
                    passedStr = 'PASSED'
                else:
                    passedStr = 'FAILED'
                row = ['-> ' + subscores['description'], str(passedStr)]
                print("{: <65} {: >11}".format(*row))
            else:
                if 'isBonus' in subscores and subscores['isBonus']:
                    row = ['-> ' + subscores['description'], "+" + str(subscore), "/" + str(subscores['scale'])]
                    print("{: <65} {: >5} {: >5}".format(*row))
                else:
                    row = ['-> ' + subscores['description'], str(subscore), "/" + str(subscores['scale'])]
                    print("{: <65} {: >5} {: >5}".format(*row))

            if not 'passed' in subscores:
                if 'isBonus' in subscores and subscores['isBonus']:
                    bonusProblemScore = bonusProblemScore + subscore
                    bonusProblemScale = bonusProblemScale + subscores['scale']
                else:
                    totalProblemScore = totalProblemScore + subscore
                    totalProblemScale = totalProblemScale + subscores['scale']
        
            # Round score
            totalProblemScore = round(totalProblemScore * 100) / 100
            totalProblemScale = round(totalProblemScale * 100) / 100

            if problemInvalidated:
                totalProblemScore = 0
                bonusProblemScore = 0
                if totalProblemScale > 0:
                    row = ['TOTAL', 'FAILED']
                    print("{: <65} {: >11}".format(*row))
                if bonusProblemScale > 0:
                    row = ['BONUS', 'FAILED']
                    print("{: <65} {: >11}".format(*row))
            else:
                if totalProblemScale > 0:
                    row = ['TOTAL', str(totalProblemScore), "/" + str(totalProblemScale)]
                    print("{: <65} {: >5} {: >5}".format(*row))
                if bonusProblemScale > 0:
                    row = ['BONUS', "+" + str(bonusProblemScore), "/" + str(bonusProblemScale)]
                    print("{: <65} {: >5} {: >5}".format(*row))
        print("")

        totalScore = totalScore + totalProblemScore
        totalScale = totalScale + totalProblemScale
        bonusScore = bonusScore + bonusProblemScore
        bonusScale = bonusScale + bonusProblemScale
        scoresJSON['scores'][problem] = totalProblemScore + bonusProblemScore
    
    print("------------------------------------------------------------------------------")
    row = ['Total score', str(totalScore), "/" + str(totalScale)]
    print("{: <65} {: >5} {: >5}".format(*row))
    if bonusScale > 0:
        row = ['Bonus', "+" + str(bonusScore), "/" + str(bonusScale)]
        print("{: <65} {: >5} {: >5}".format(*row))
        row = ['TOTAL', str(bonusScore + totalScore), "/" + str(totalScale)]
        print("{: <65} {: >5} {: >5}".format(*row))
        
    print("------------------------------------------------------------------------------")
    # if not handoutMode:
    print(json.dumps(scoresJSON))

if __name__ == "__main__":
    with open('./grader/result.log', 'r') as result_file:
        interpretResults(result_file)
