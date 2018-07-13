The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for enu.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on enu.token
0. Create MES token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`mycleos wallet create`

### Create account steps
`mycleos create key`

`mycleos create key`

`mycleos wallet import <private key from step 1>`

`mycleos wallet import <private key from step 2>`

`mycleos create account myeosio <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`mycleos set contract enu.token /contracts/enu.token -p enu.token@active`

### Create MES token steps
`mycleos push action enu.token create '{"issuer": "enu.token", "maximum_supply": "100000.0000 MES", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p enu.token@active`

### Issue token steps
`mycleos push action enu.token issue '{"to": "scott", "quantity": "900.0000 MES", "memo": "testing"}' -p enu.token@active`
