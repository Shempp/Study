'use strict';

angular.
    module('rentalpropertyApp').
    config(['$routeProvider', function config($routeProvider) {
        $routeProvider.
        when('/', {
          template: '<renting-items-list></renting-items-list>'
        }).
        when('/:rentingItemId', {
          template: '<renting-item-detail></renting-item-detail>'
        }).
        otherwise('/');
    }
    ]);