'use strict';

angular.
    module('rentingItemDetail').
    component('rentingItemDetail', {
        template: 'TBD: Detail view for <span>{{$ctrl.id}}</span>',
        controller: ['$routeParams', function RentingItemDetailController($routeParams, $http, $location) {


             // REST HTTP GET
            //$http.get('http://127.0.0.1:8000/api/rentingitems/').then(function(response) {
                //self.rentingItems = response.data;
            //});

            this.id = $routeParams.rentingItemId;
            console.log(this.id);
        }
        ]
    });
