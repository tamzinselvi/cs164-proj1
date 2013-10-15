
class Morphism of [$Domain, $Codomain]:
    rule::($Domain)->$Codomain = None
    def __init__(self, rule::($Domain)->$Codomain):
        self.rule = rule

def sign_string(x::Int)::Str:
    if x > 0:
        return "positive"
    elif x < 0:
        return "negative"
    else:
        return "zero"

M:: Morphism of [Int, Str] = Morphism of [Int, Str](sign_string)

print M.rule(5)
