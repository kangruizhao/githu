from django.shortcuts import render,redirect
from .models import Snack,Drink
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
import json
from itertools import chain

#display the menu of the drink and snack
def index(request):

     Snacks_list = Snack.objects.all();
     Drink_list=Drink.objects.all();
     combine= list(chain(Snacks_list, Drink_list))
     context = {'food_list': combine}
     return render(request, 'inventory/index.html',context)
#delete food from inventory
def delete(request,foodtype,_id):
    if (foodtype=="Drink"):
        food_will_delete=Drink.objects.filter(id=_id)
    else:
        food_will_delete=Snack.objects.filter(id=_id)
    food_will_delete.delete()
    return redirect(index)
#show the edit page
def edit(request,foodtype,_id):
    if (foodtype=="Drink"):
        food_will_edit=Drink.objects.filter(id=_id).first()
        already_recommand=food_will_edit.snack_set.values_list('id').all();
        list_of_rest_food_as_recommand=Snack.objects.all();

    else:
        food_will_edit=Snack.objects.filter(id=_id).first()
        already_recommand=food_will_edit.recommended_drink.values_list('id');
        list_of_rest_food_as_recommand=Drink.objects.all();
    context = {'food_list': list_of_rest_food_as_recommand,
                'food_will_edit':food_will_edit
                }
    return render(request, 'inventory/edit.html',context)
#Post method of edit the food
def editsomething(request,foodtype,_id):
    name=request.POST['Name']
    ingredients=request.POST['Ingredients']
    recommends=request.POST.getlist('selectrecommand')
    if (foodtype=="Drink"):
        food_will_edit=Snack.objects.filter(id=_id).first()
        if (len(recommends)>0):
            food_will_edit.snack_set.clear()
            for x in recommends:
                tmp=Drink.objects.filter(sname=x).first();
                food_will_edit.snack_set.add(tmp)
    else:
        food_will_edit=Snack.objects.filter(id=_id).first()
        if (len(recommends)>0):
            food_will_edit.recommended_drink.clear()
            for x in recommends:
                tmp=Drink.objects.filter(sname=x).first();
                food_will_edit.recommended_drink.add(tmp)
    food_will_edit.sname=name;
    food_will_edit.ingredients=ingredients;
    food_will_edit.save();
    return redirect(index)





# to the page of add drink or snack
def add(request):

    return render(request, 'inventory/add.html')
#  add drink or snack
def addsomething(request):
    name=request.POST['Name']
    ingredients=request.POST['Ingredients']
    type=request.POST['selecttype']
    recommends=request.POST.getlist('selectrecommand')
    print(type)
    if(type=='drink'):
        s=Drink(sname=name,ingredients=ingredients);
        s.save()
        if (len(recommends)>0):
            for x in recommends:
                tmp=Snack.objects.filter(sname=x).first();
                s.snack_set.add(tmp)
        s.save()
    else :
        s=Snack(sname=name,ingredients=ingredients);
        s.save()
        if (len(recommends)>0):
            for x in recommends:
                tmp=Drink.objects.filter(sname=x).first();
                s.recommended_drink.add(tmp)
        s.save()

    return redirect(index)
# for the display the selection of A list of recommended snacks/drink from the menu that pair well with the drink/snack
# when you try to add snacks/drink to the inventory.
@csrf_exempt
def getdetails(request):


    type = request.POST.get('selecttype', False);

    print(type)
    result_set = []
    if(type=='Drink'):
       recommendeds = Snack.objects.all();
    else:
       recommendeds = Drink.objects.all();


    #//print "selected country name ", selected_country
    for recommendeds in recommendeds:
        result_set.append({'name': recommendeds.sname})
    print(result_set)

    return HttpResponse(json.dumps(result_set), content_type='application/json')
