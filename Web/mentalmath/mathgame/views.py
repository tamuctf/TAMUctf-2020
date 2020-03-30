from django.shortcuts import render
from django.http import JsonResponse
import random

def index(request):
    return render(request, 'mathgame/index.html')

def play(request):
    return render(request, 'mathgame/play.html')

def new_problem(request):
    response_data = {}

    if request.method == "POST" and request.is_ajax() and len(request.POST['problem']) > 0:
        problem = request.POST['problem']
        answer = request.POST['answer']
        if eval(problem) == int(answer):
            response_data['correct'] = True
            response_data['problem'] = gen_problem()
        else:
            response_data['correct'] = False
    else:
        response_data['correct'] = True
        response_data['problem'] = gen_problem()

    return JsonResponse(response_data)

def gen_problem():
    ops = '+*-'
    a, b = random.randint(0, 100), random.randint(0, 100)
    return str(a) + ' ' + random.choice(ops) + ' ' + str(b)
